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
#include "struct_def.h"
#include "key_pressed.h"
#include "linked_list.h"
#include "menu.h"
//detect leak
//#include "leakdetector/leak_detector_c.h"

//coord 0:0 => en haut a gauche

void *Game(void* _threadArgs)
{
  Env *args = (Env*) _threadArgs;
  LinkedList *shipList = initialization(args->list2free);
  int nbEnemyToSpawn = 10, listsizeTotal = shipList->top->hitbox->x;

  int counter = 0;
  int enemyID = 1;
  int nbFriendlyShipLives = args->nbFriendlyShipLives;
  int protectedOnHit=0, protectedCounter=0, redON=0;

  int fileSizeShip1, fileSizeShip2;
  char *shipFile1 = GetShip("../assets/Vaisseaux/ennemis/TestShip.txt", &fileSizeShip1);
  char *shipFile2 = GetShip("../assets/Vaisseaux/ennemis/Enemy_MotherShip.txt", &fileSizeShip2);

  main_ship *myShip = args->ship;
  myShip->coord->x = (args->xmax)/2;
  myShip->coord->y = (args->ymax)-1;

  fireInst *fireChain[args->nbMissiles];
  for (int i = 0; i < args->nbMissiles; i++)
  {
    fireChain[i] = (fireInst*)malloc(sizeof(fireInst));
    registerFree(args->list2free, fireChain[i]);
    fireChain[i]->coord = (coordinate*)malloc(sizeof(coordinate));
    fireChain[i]->state = 0;
  }

  system("clear");
  int getShipWidth=0;
  int shipHeight = displayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x, &getShipWidth);
  char a;
  char direction = 'r';

  for (int i=0; i < nbEnemyToSpawn; i++)
  {
    addShip(shipList, getShipWidth);
    listsizeTotal += (shipList->top->hitbox->x - shipList->top->coord->x);
    shipList->top->hitbox->y += shipHeight;
  }

  fireInst *fireChainEnemy[args->nbEnemiesMissiles];
  for (int i = 0; i < args->nbEnemiesMissiles; i++)
  {
  fireChainEnemy[i] = (fireInst *)malloc(sizeof(fireInst));
  registerFree(args->list2free, fireChainEnemy);
  fireChainEnemy[i]->coord = (coordinate *)malloc(sizeof(coordinate));
  fireChainEnemy[i]->state = 0;
  }
  srand(time(NULL));
  int numberOfEnemiesFiring=0, numberOfEnemiesAlive=1;

  printf("\033[%d;%dH", myShip->coord->y, myShip->coord->x);
  while (1)
  {
    printf("\033[1;37m");
    if (shipList->top != NULL)
    {
      counter++;
      if (counter == 2)
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
          eraseList(shipList, fileSizeShip1, shipFile1);
          displayList(shipList, fileSizeShip1, shipFile1, direction);
        }

        if (direction == 'l')
        {
          eraseList(shipList, fileSizeShip1, shipFile1);
          displayList(shipList, fileSizeShip1, shipFile1, direction);
        }
      }
    }

    for (int i = 0; i < args->nbMissiles ; i++)
    {
      if(fireChain[i]->state == 1)
      {
        enemyID = 1;
        if(shipList->top != NULL && fireChain[i]->relativePosY - fireChain[i]->coord->y < 15)
        {
          fireMissile(fireChain[i]->coord->x, fireChain[i]->relativePosY);
          fireChain[i]->relativePosY = fireChain[i]->relativePosY - 1;
          enemy *current = shipList->top;
          while (current != NULL)
          {
            if(fireChain[i]->relativePosY <= current->hitbox->y && fireChain[i]->coord->x > current->coord->x && fireChain[i]->coord->x < current->hitbox->x)
            {
              removeShip(shipList, fileSizeShip1, shipFile1, enemyID);
              printf("\033[%d;%dH%c ", fireChain[i]->relativePosY+1, fireChain[i]->coord->x, ' ');  
              fireChain[i]->state = 0;
              fireChain[i]->relativePosY = fireChain[i]->coord->y;
              numberOfEnemiesAlive--; //To avoid seg fault if the next random enemy ship to fire is the one just killed
              break;
            }
            enemyID++;
            current = current->next;
          }
          
          if ((fireChain[i]->coord->y - fireChain[i]->relativePosY) > (args->ymax)-shipHeight+2)
          {
            printf("\033[%d;%dH ",  fireChain[i]->relativePosY, fireChain[i]->coord->x);  
            fireChain[i]->state = 0;
            fireChain[i]->relativePosY = fireChain[i]->coord->y;
            break;
          }
        } 
      }
    }

    if (((rand() % (10 - 1 + 1)) + 1 == 2) && (shipList->top != NULL))
    {
      for (int enemyFireAvailabiltyChecker = 0; enemyFireAvailabiltyChecker < args->nbEnemiesMissiles; enemyFireAvailabiltyChecker++)
      {
        if (fireChainEnemy[enemyFireAvailabiltyChecker]->state == 0)
        {
          int firingEnemyID = (rand() % (numberOfEnemiesAlive - 1 + 1)) + 1;
          enemy *firingEnemy = getShipByID(shipList, firingEnemyID);
          fireChainEnemy[enemyFireAvailabiltyChecker]->state = 1;
          fireChainEnemy[enemyFireAvailabiltyChecker]->coord->x = firingEnemy->coord->x + 4;
          fireChainEnemy[enemyFireAvailabiltyChecker]->relativePosY = (firingEnemy->coord->y) + shipHeight+1;
          break;
        }
      }
    }

for (int i = 0; i < args->nbEnemiesMissiles; i++)
{
  if (fireChainEnemy[i]->state == 1)
  {
    if (fireChainEnemy[i]->relativePosY < args->ymax+shipHeight)
    {
      enemyFireMissile(fireChainEnemy[i]->coord->x, fireChainEnemy[i]->relativePosY);
      fireChainEnemy[i]->relativePosY = fireChainEnemy[i]->relativePosY + 1;
      if (fireChainEnemy[i]->relativePosY > (args->ymax - 1) && fireChainEnemy[i]->coord->x > myShip->coord->x && fireChainEnemy[i]->coord->x < myShip->coord->x +getShipWidth && protectedOnHit == 0)
      {
        nbFriendlyShipLives--;
        fireChainEnemy[i]->state = 0;
        printf("\033[%d;%dH ", fireChainEnemy[i]->relativePosY - 1, fireChainEnemy[i]->coord->x);
        displayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x, &getShipWidth);
        protectedOnHit=1;
        if (nbFriendlyShipLives<1)
        {
          *(args->isGameDone_ptr) = 1;
          return NULL; // change this to GAME OVER function
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

  if (protectedOnHit!=0)
  {
    if (redON != 0)
    {
      printf("\033[1;31m");
      displayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x, &getShipWidth);
    }
    else
    {
      printf("\033[1;37m");
      displayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x, &getShipWidth);
    }
    if (protectedCounter % 20 == 0)
    {
      if (redON != 1)
      {
        redON = 1;
        printf("\033[1;31m");
        displayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x, &getShipWidth);
      }
      else
      {
        redON = 0;
        printf("\033[1;37m");
        displayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x, &getShipWidth);
      }
    }
    protectedCounter++;
    if (protectedCounter > 100)
    {
      printf("\033[1;37m");
      displayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x, &getShipWidth);
      protectedCounter=0;
      protectedOnHit=0;
    }
  }
    usleep(args->gameSpeed); //Missile speed - increase to lower speed / decrease to higher speed
    a=*(args->keyPressed);
      if (a != 0) //Ship movement
      {
        if (a == SPAWN)
        {
          removeShip(shipList, fileSizeShip1, shipFile1, 1);
        }
        if (a == 'm')
        {
          eraseList(shipList, fileSizeShip1, shipFile1);
        }
        if (a == LEFT)
        {         
          if ((myShip->coord->x-4)>0)  //Prevent moving over terminal limit
          {
            eraseShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x);
            myShip->coord->x=myShip->coord->x-4;
            displayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x, &getShipWidth);
            continue;
          }
        }
        if (a == RIGHT)
        {
          if ((myShip->coord->x + 8) < args->xmax) //Prevent moving over terminal limit
          {
            eraseShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x);
            myShip->coord->x = myShip->coord->x + 4;
            displayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x, &getShipWidth);
            continue;
          }
        }
        if (a == FIRE)
        {
          for (int i = 0; i < args->nbMissiles ; i++)
          {
            if (fireChain[i]->state == 0)
            {
              fireChain[i]->coord->y = (myShip->coord->y)-2;
              fireChain[i]->relativePosY = fireChain[i]->coord->y;
              fireChain[i]->coord->x = (myShip->coord->x)+4;
              fireChain[i]->state = 1;
              break;
            }
          }
        }

        if (a == QUIT)
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
  int gameType= 0;
  system("clear");
  printf("\e[?25l"); //hide the terminal cursor

  struct termios t;   //Struct to block any keyboard input on the Linux Terminal
  tcgetattr(0, &t);
  t.c_lflag &= ~ECHO;
  tcsetattr(0, TCSANOW, &t);

  struct winsize w;  //Struct to get Linux Terminal size
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int ymax=w.ws_row-4;
  int xmax=w.ws_col-2;
  int isGameDone = 0;

  pthread_t thread_id;

  Env *args = (Env*)malloc(sizeof(Env));
  args->list2free = (linkedMalloc*)malloc(sizeof(linkedMalloc));
  args->ship = (main_ship*)malloc(sizeof(main_ship));
  args->ship->coord = (coordinate*)malloc(sizeof(coordinate));
  
  args->isGameDone_ptr = &isGameDone;
  args->xmax = xmax;
  args->ymax = ymax;
  args->keyPressed = &keyPressed;
  //print menu
  gameType = menu_instance(args);
  switch (gameType)
  {
    case EASY:
      args->nbEnemy = 2;
      args->nbMissiles = 6;
      args->nbEnemiesMissiles = 2;
      args->nbFriendlyShipLives = 3;
      args->gameSpeed = 19000;
      break;
    case NORMAL:
      args->nbEnemy = 5;
      args->nbMissiles = 4;
      args->nbEnemiesMissiles = 4;
      args->nbFriendlyShipLives = 2;
      args->gameSpeed = 17000;
      break;
    case IMPOSSIBLE:
      args->nbEnemy = 10;
      args->nbMissiles = 2;
      args->nbEnemiesMissiles = 6;
      args->nbFriendlyShipLives = 1;
      args->gameSpeed = 15000;
      break;
    case QUIT:
      system("reset");
      free(args);
      exit(0);
      break;

    default:
      break;
  }
  pthread_create(&thread_id, NULL, Game, (void*)args);

  while (1)
  {
   if (*(args->isGameDone_ptr) == 1) {
       pthread_join(thread_id, NULL);
       break;
    } 
    keyPressed=key_pressed();
    usleep(20000);
  }
  freeRegistered(args->list2free);
  free(args);
  //atexit(report_mem_leak);
  system("clear");
  system("reset");
  return 0;
}