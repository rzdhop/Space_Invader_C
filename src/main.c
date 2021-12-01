#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include "struct_def.h"
#include "key_pressed.h"
#include "linked_list.h"

//coord 0:0 => en haut a gauche
#define MAX_MISSILES 6

void *keystrokeInstanceHandler(void* _threadArgs)
{
  args_thread *args = (args_thread*) _threadArgs;
  LinkedList *shipList = initialization();
  LinkedList *saveTheMailleTemp;
  int nbEnemyToSpawn = 10, listsizeTotal = shipList->maille->hitbox->x;

  int counter =0;

  int fileSizeShip1, fileSizeShip2;
  char *shipFile1 = GetShip("../assets/Vaisseaux/ennemis/TestShip.txt", &fileSizeShip1);
  char *shipFile2 = GetShip("../assets/Vaisseaux/ennemis/Enemy_MotherShip.txt", &fileSizeShip2);

  main_ship *myShip = args->ship;
  myShip->coord->x = (args->xmax)/2;
  myShip->coord->y = (args->ymax)-1;

  enemy *eShip = (enemy*)malloc(sizeof(enemy));
  eShip->state = 1;
  eShip->coord = (coordinate*)malloc(sizeof(coordinate));
  eShip->coord->x = (args->xmax)/2;
  eShip->coord->y = 1;

  fireInst *fireChain[MAX_MISSILES];
  for (int i = 0; i < MAX_MISSILES; i++)
  {
    fireChain[i] = (fireInst*)malloc(sizeof(fireInst));
    fireChain[i]->coord = (coordinate*)malloc(sizeof(coordinate));
    fireChain[i]->state = 0;
  }

  int shipHeight = diplayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x);
  int eShipCnt=1;
  char a;
  char direction = 'l';

  for (int i=0; i < nbEnemyToSpawn; i++)
  {
    addShip(shipList);
    listsizeTotal += (shipList->maille->hitbox->x - shipList->maille->coord->x);
    shipList->maille->state = 1;
    shipList->maille->hitbox->y += shipHeight;
  }

  printf("\033[%d;%dH", myShip->coord->y, myShip->coord->x);
  while (1)
  {
    if (shipList->maille != NULL)
    {
      counter++;
      if (counter == 8)
      {
        counter = 0;
        if (eShipCnt + listsizeTotal > args->xmax-listsizeTotal/2 -15) //solution temporaire
        {
          direction = 'l';
        }
        if (eShipCnt < 1)
        { 

          direction = 'r';
        }
        if (direction == 'r')
        {
          eShipCnt++;//relative coordinate %8
          eraseList(shipList, fileSizeShip1, shipFile1);
          displayList(shipList, fileSizeShip1, shipFile1, direction);
        }

        if (direction == 'l')
        {
          eShipCnt--;
          eraseList(shipList, fileSizeShip1, shipFile1);
          displayList(shipList, fileSizeShip1, shipFile1, direction);
        }
      }
    }
    enemy *current = shipList->maille;
    int tempflag = 0;
    while(current != NULL)
    {
      for (int i = 0; i < MAX_MISSILES; i++)
      {
        if(fireChain[i]->state == 1)
        {
            if(!tempflag)
            {
              fireMissile(fireChain[i]->coord->x, fireChain[i]->relativePosY);
              fireChain[i]->relativePosY = fireChain[i]->relativePosY - 1;
            }
            if(fireChain[i]->relativePosY <= current->hitbox->y && fireChain[i]->coord->x > current->coord->x && fireChain[i]->coord->x < current->hitbox->x)
            {
              if(current->state)
              {
                removeShip(shipList, fileSizeShip1, shipFile1, current->enemyID);
                printf("\033[%d;%dH%c ", fireChain[i]->relativePosY+1, fireChain[i]->coord->x, ' ');  
                fireChain[i]->state = 0;
                break;
              }
            }
            if ((fireChain[i]->coord->y - fireChain[i]->relativePosY) > (args->ymax)-shipHeight+2)
            {
              printf("\033[%d;%dH ",  fireChain[i]->relativePosY, fireChain[i]->coord->x);  
              fireChain[i]->state = 0;
              break;
            } 
        }
      }
      tempflag = 1;
      current = current->next;
    }

    usleep(18000); //Missile speed - increase to lower speed / decrease to higher speed
    a=*(args->keyPressed);
      if (a != 0) //Ship movement
      {
        if (a == SPAWN)
        {
          eShipCnt=0;
        }
        if (a == LEFT)
        {
          if ((myShip->coord->x-4)>0)  //Prevent moving over terminal limit
          {
          eraseShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x);
          myShip->coord->x=myShip->coord->x-4;
          diplayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x);
          continue;
          }
        }
        if (a == RIGHT)
        {
          if ((myShip->coord->x+4)< args->xmax) //Prevent moving over terminal limit
          {
          eraseShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x);
          myShip->coord->x=myShip->coord->x+4;
          diplayShip(fileSizeShip1, shipFile1, myShip->coord->y, myShip->coord->x);
          continue;
          }
        }
        if (a == FIRE)
        {
          for (int i = 0; i < MAX_MISSILES; i++)
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
  system("clear");
  printf("\e[?25l"); //hide the terminal cursor

  struct termios t;   //Struct to block any keyboard input on the Linux Terminal
  tcgetattr(0, &t);
  t.c_lflag &= ~ECHO;
  tcsetattr(0, TCSANOW, &t);

  struct winsize w;  //Struct to get Linux Terminal size
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int ymax=w.ws_row-4;
  int xmax=w.ws_col-7;
  int isGameDone = 0;

  pthread_t thread_id;

  args_thread *args = (args_thread*)malloc(sizeof(args_thread));
  args->ship = (main_ship*)malloc(sizeof(main_ship));
  args->ship->coord = (coordinate*)malloc(sizeof(coordinate));
  
  args->isGameDone_ptr = &isGameDone;
  args->xmax = xmax;
  args->ymax = ymax;
  args->keyPressed = &keyPressed;

  pthread_create(&thread_id, NULL, keystrokeInstanceHandler, (void*)args);
  while (1)
  {
   if (*(args->isGameDone_ptr) == 1) {
       pthread_join(thread_id, NULL);
       break;
    } 
    keyPressed=key_pressed();
    usleep(20000);
  }
  system("reset");
  return 0;
}