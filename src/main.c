#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <malloc.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <time.h>
#include "struct_def.h" //Contien la majorité des structures utilisé pour le jeu 
#include "key_pressed.h" //Contien le code relatif au saisies clavier 
#include "linked_list.h" //Contien le code relatif au listes chainées 
#include "menu.h" //Contien le code relatif a l'affichage du menu principale, ecran de victoire et d'echec
#include "colors.h" //Contien la definition des couleurs 

//coord 0:0 => en haut a gauche

void *Game(void* _threadArgs) //Instance de partie 
{
  //recupère les argument de l'environnement de jeu
  Env *args = (Env*) _threadArgs;
  int nbEnemyToSpawn = args->nbEnemy;

  int counter = 0;
  int enemyID = 1;
  int nbFriendlyShipLives = args->nbFriendlyShipLives;
  int protectedOnHit=0, protectedCounter=0, redON=0;

  //récupère les fichiers des vaisseaux
  int fileSizeShip1, fileSizeShip2;
  char *shipFile1 = GetShip("../assets/Vaisseaux/ennemis/MyShip.txt", &fileSizeShip1);
  char *shipFile2 = GetShip("../assets/Vaisseaux/ennemis/EnemyShip.txt", &fileSizeShip2);

  //Crée le vaisseau allié
  main_ship *myShip = args->ship;
  myShip->coord->x = (args->xmax)/2;
  myShip->coord->y = (args->ymax)-1;

  //Crée les instances de missiles
  fireInst *fireChain[args->nbMissiles];
  for (int i = 0; i < args->nbMissiles; i++)
  {
    fireChain[i] = (fireInst*)malloc(sizeof(fireInst));
    registerFree(args->list2free, fireChain[i]);
    fireChain[i]->coord = (coordinate*)malloc(sizeof(coordinate));
    fireChain[i]->state = 0;
  }

  //récupere plusieurs donnée d'environnements
  int getMyShipWidth=0, getEnemyShipWidth;
  int myShipHeight = displayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x, &getMyShipWidth);
  int enemyShipHeight = displayShip(fileSizeShip2, shipFile2, 5, 5, &getEnemyShipWidth);
  eraseShip(fileSizeShip2, shipFile2, 5, 5);
  char a;
  char direction = 'r';

  //Crée la liste chainée 
  LinkedList *shipList = initialization(args->list2free, getEnemyShipWidth, enemyShipHeight);

  for (int i=0; i < nbEnemyToSpawn; i++)
  {
    addShip(shipList, getEnemyShipWidth);
  }

  //Crée les instances de missiles enemies
  fireInst *fireChainEnemy[args->nbEnemiesMissiles];
  for (int i = 0; i < args->nbEnemiesMissiles; i++)
  {
  fireChainEnemy[i] = (fireInst *)malloc(sizeof(fireInst));
  registerFree(args->list2free, fireChainEnemy);
  fireChainEnemy[i]->coord = (coordinate *)malloc(sizeof(coordinate));
  fireChainEnemy[i]->state = 0;
  }
  //initialise le rand 
  srand(time(NULL));
  int numberOfEnemiesFiring=0, numberOfEnemiesAlive=1;
  int starsTimer=0, posY[10], posX[10];


  printf("\033[%d;%dH", myShip->coord->y, myShip->coord->x);
  fflush(stdout);
  sleep(1);
  while (1) //************************************************************************
  {
    //Affiche les statistiques de la partie en cours
    printf("\033[%d;%dH Score :%d", 10, 2, args->score);
    printf("\033[%d;%dH Vie   :%d", 11, 2, nbFriendlyShipLives);
    //verifie si la partie est fini (sinon augmente la difficultée)
    if(numberOfEnemiesAlive == 0 && args->gameType != IMPOSSIBLE)
    {
      winScreen(args);
      return NULL;
    }
    else if( numberOfEnemiesAlive == 0 && args->gameType == IMPOSSIBLE)
    {
      *(args->isGameDone_ptr) = 3;
      return NULL;
    }
    printf(YELLOW);

    //affiche les etoiles en fond
    if (starsTimer % 120 == 0)
    {
      for (int i = 0; i < 10; i++)
      {
        printf("\033[%d;%dH ", posY[i], posX[i]);
        posY[i] = ((rand() % (args->ymax - 1 + 1)) + 1);
        posX[i] = ((rand() % (args->xmax - 1 + 1)) + 1);
        printf("\033[%d;%dH*", posY[i], posX[i]);
      }
      starsTimer = 0;
    }
    starsTimer++;
    printf(WHITE);

    //Partie de code pour le deplacement latéral des enemies 
    if (shipList->top != NULL)
    {
      counter++;
      if (counter == 10)
      {
        counter = 0;
        if (shipList->top->hitbox->x > args->xmax)
        {
          direction = 'l';
        }
        enemy *lastOfLinkedList = getLastOfLinkedList(shipList, &numberOfEnemiesAlive);

        if (lastOfLinkedList->coord->x < 1)
        { 
          direction = 'r';
        }
        if (direction == 'r')
        {
          eraseList(shipList, fileSizeShip2, shipFile2);
          displayList(shipList, fileSizeShip2, shipFile2, direction);
        }

        if (direction == 'l')
        {
          eraseList(shipList, fileSizeShip2, shipFile2);
          displayList(shipList, fileSizeShip2, shipFile2, direction);
        }
      }
    }

    //pour les missiles actifs verifie leur position (si il sont en contacte avec un enemie) et le deplace/supprime sinon
    for (int i = 0; i < args->nbMissiles; i++)
    {
      if (fireChain[i]->state == 1)
      {
        enemyID = 1;
        fireMissile(fireChain[i]->coord->x, fireChain[i]->relativePosY);
        fireChain[i]->relativePosY = fireChain[i]->relativePosY - 1;
        enemy *current = shipList->top;
        while (current != NULL)
        {
          if (fireChain[i]->relativePosY <= (current->hitbox->y - 1) && fireChain[i]->coord->x > current->coord->x && fireChain[i]->coord->x < current->hitbox->x)
          {
            current->nbOfLives -= 1;
            printf("\033[%d;%dH%c", fireChain[i]->relativePosY + 1, fireChain[i]->coord->x, ' ');
            fireChain[i]->state = 0;
            fireChain[i]->relativePosY = fireChain[i]->coord->y;
            if (current->nbOfLives < 1)
            {
              args->score += 20;
              removeShip(shipList, fileSizeShip2, shipFile2, enemyID);
              numberOfEnemiesAlive--; //To avoid seg fault if the next random enemy ship to fire is the one just killed
            }else {
              args->score +=10;
            }
            break;
          }
          enemyID++;
          current = current->next;
        }

        if (fireChain[i]->relativePosY < 0)
        {
          printf("\033[%d;%dH ", fireChain[i]->relativePosY, fireChain[i]->coord->x);
          fireChain[i]->state = 0;
          fireChain[i]->relativePosY = fireChain[i]->coord->y;
          break;
        }
      }
    }

    //Partie de code résponsable du tire a fréquence aléatoire des enemies
    if (((rand() % (10 - 1 + 1)) + 1 == 2) && (shipList->top != NULL))
    {
      for (int enemyFireAvailabiltyChecker = 0; enemyFireAvailabiltyChecker < args->nbEnemiesMissiles; enemyFireAvailabiltyChecker++)
      {
        if (fireChainEnemy[enemyFireAvailabiltyChecker]->state == 0)
        {
          int firingEnemyID = (rand() % (numberOfEnemiesAlive - 1 + 1)) + 1;
          enemy *firingEnemy = getShipByID(shipList, firingEnemyID);
          fireChainEnemy[enemyFireAvailabiltyChecker]->state = 1;
          fireChainEnemy[enemyFireAvailabiltyChecker]->coord->x = firingEnemy->coord->x + 6;
          fireChainEnemy[enemyFireAvailabiltyChecker]->relativePosY = (firingEnemy->coord->y) + enemyShipHeight;
          break;
        }
      }
    }

//partie de code résponsable des missiles tiré par le joueur
for (int i = 0; i < args->nbEnemiesMissiles; i++)
{
  if (fireChainEnemy[i]->state == 1)
  {
    if (fireChainEnemy[i]->relativePosY < args->ymax+myShipHeight)
    {
      enemyFireMissile(fireChainEnemy[i]->coord->x, fireChainEnemy[i]->relativePosY);
      fireChainEnemy[i]->relativePosY = fireChainEnemy[i]->relativePosY + 1;
      if (fireChainEnemy[i]->relativePosY > (args->ymax - 1) && fireChainEnemy[i]->coord->x > myShip->coord->x && fireChainEnemy[i]->coord->x < myShip->coord->x +getMyShipWidth && protectedOnHit == 0)
      {
        nbFriendlyShipLives--;
        fireChainEnemy[i]->state = 0;
        printf("\033[%d;%dH ", fireChainEnemy[i]->relativePosY - 1, fireChainEnemy[i]->coord->x);
        displayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x, &getMyShipWidth);
        protectedOnHit=1;
        if (nbFriendlyShipLives<1) //Verifi si le joueur n'as plus de vie
        {
          fflush(stdout);
          sleep(1);
          looseScreen(args);
          return NULL;
        }
      }
    }
    else
    {
      printf("\033[%d;%dH ", fireChainEnemy[i]->relativePosY - 1, fireChainEnemy[i]->coord->x);
      fireChainEnemy[i]->state = 0;
    }
  }
}
  //Permet au joueru apres avoir subis un degat d'etre invincible temporairement (signal coloré)
  if (protectedOnHit!=0)
  {
    if (redON != 0)
    {
      printf(RED);
      displayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x, &getMyShipWidth);
    }
    else
    {
      printf(WHITE);
      displayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x, &getMyShipWidth);
    }
    if (protectedCounter % 20 == 0)
    {
      if (redON != 1)
      {
        redON = 1;
        printf(RED);
        displayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x, &getMyShipWidth);
      }
      else
      {
        redON = 0;
        printf(WHITE);
        displayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x, &getMyShipWidth);
      }
    }
    protectedCounter++;
    if (protectedCounter > 100)
    {
      printf(WHITE);
      displayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x, &getMyShipWidth);
      protectedCounter=0;
      protectedOnHit=0;
    }
  }
    //Permet de gerer la cadence du jeux 
    usleep(args->gameSpeed); //Missile speed - increase to lower speed / decrease to higher speed
    a=*(args->keyPressed); //verifie l'entré clavier du joueur
      if (a != 0) //Ship movement
      {
        if (a == LEFT)
        {         
          if ((myShip->coord->x-4)>0)  //Verfie que le joueur ne depasse pas la limite du terminal 
          {
            eraseShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x);
            myShip->coord->x=myShip->coord->x-4;
            displayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x, &getMyShipWidth);
            continue;
          }
        }
        if (a == RIGHT)
        {
          if ((myShip->coord->x + 8) < args->xmax) //Verfie que le joueur ne depasse pas la limite du terminal 
          {
            eraseShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x);
            myShip->coord->x = myShip->coord->x + 4;
            displayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x, &getMyShipWidth);
            continue;
          }
        }
        if (a == FIRE) //Initialise un nouveau missile si l'utilisateur Tire
        {
          for (int i = 0; i < args->nbMissiles ; i++)
          {
            if (fireChain[i]->state == 0)
            {
              fireChain[i]->coord->y = (myShip->coord->y)-1;
              fireChain[i]->relativePosY = fireChain[i]->coord->y;
              fireChain[i]->coord->x = (myShip->coord->x)+4;
              fireChain[i]->state = 1;
              break;
            }
          }
        }

        if (a == QUIT) //met fin au jeu 
        {
          *(args->isGameDone_ptr) = 1;
          return NULL;
        }
      }
  }
  return NULL;
}

int main(void){
  char keyPressed;
  int gameType= 0, replay =0;
  system("clear");
  printf("\e[?25l"); //Cache le curseur sur le terminal 

  struct termios t;   //Permet de blocker les entré du terminal 
  tcgetattr(0, &t);
  t.c_lflag &= ~ECHO;
  tcsetattr(0, TCSANOW, &t);

  struct winsize w;  //Permet de récuperer la taille du terminal
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int ymax=w.ws_row-4;
  int xmax=w.ws_col-2;
  int isGameDone = 0;

  pthread_t thread_id; //initialise de thread

  //Initialise les valeur de l'environnement de jeux
  Env *args = (Env*)malloc(sizeof(Env));
  args->list2free = (linkedMalloc*)malloc(sizeof(linkedMalloc)); //Liste chainé faisant office de garbage collector 
  args->ship = (main_ship*)malloc(sizeof(main_ship));
  args->ship->coord = (coordinate*)malloc(sizeof(coordinate));
  
  args->isGameDone_ptr = &isGameDone;
  args->xmax = xmax;
  args->ymax = ymax;
  args->keyPressed = &keyPressed;
  args->score = 0;
  //Affiche le menu de choix du type de jeu
  gameType = menu_instance(args);
  switch (gameType)
  {
    case EASY:
      args->nbEnemy = 2;
      args->nbMissiles = 6;
      args->nbEnemiesMissiles = 2;
      args->nbFriendlyShipLives = 3;
      args->gameSpeed = 19000;
      args->gameType = EASY;
      break;
    case NORMAL:
      args->nbEnemy = 5;
      args->nbMissiles = 4;
      args->nbEnemiesMissiles = 4;
      args->nbFriendlyShipLives = 2;
      args->gameSpeed = 17000;
      args->gameType = NORMAL;
      break;
    case IMPOSSIBLE:
      args->nbEnemy = 2;
      args->nbMissiles = 6;
      args->nbEnemiesMissiles = 2;
      args->nbFriendlyShipLives = 3;
      args->gameSpeed = 19000;
      args->gameType = IMPOSSIBLE;
      break;
    case QUIT:
      system("reset");
      free(args);
      exit(0);
      break;

    default:
      break;
  }
  //lance le Thread
  pthread_create(&thread_id, NULL, Game, (void*)args);

  // En meme temps on verifie l'etat de la partie et récupere l'entrée utilisateur sans stopper le jeu si l'utilisateur ne bouge pas
  while (1)
  {
   if (*(args->isGameDone_ptr) == 1) { //verfie su la partie est fini 
       pthread_join(thread_id, NULL);
       break;
    } 
    if (*(args->isGameDone_ptr) == 2) { //verfie si le joeur veux rejouer
       pthread_join(thread_id, NULL);
       replay =1;
       break;
    } 
    if(*(args->isGameDone_ptr) == 3){ //si le mode est en progressif on relance une partie avec une difficulté supérieur
      while(*(args->isGameDone_ptr) == 3){
        system("clear");
        args->gameSpeed -= 1000;
        args->nbEnemiesMissiles += 1;
        args->nbEnemy += 1;
        *(args->isGameDone_ptr) = 0;
        pthread_create(&thread_id, NULL, Game, (void*)args);
      }
    }
    keyPressed=key_pressed();
    usleep(20000);
  }
  //lance le garbase collector 
  freeRegistered(args->list2free);
  free(args);
  system("clear");
  system("reset");
  if(replay) //relance le jeux
  {
    main();
  }
  return 0;
}