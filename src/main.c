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

typedef struct xy_coordinate coordinate;
struct xy_coordinate
{
  int x;
  int y;
};

typedef struct enemy_data enemy;
struct enemy_data
{
  coordinate coord;
  int state;
};

typedef struct main_friendly_ship main_ship;
struct main_friendly_ship 
{
  coordinate *coord; 
  int state;
  int life;
};

typedef struct args_struct_thread args_thread;
struct args_struct_thread
{
  main_ship *ship;
  char *keyPressed;
  int *xmax;
  int *ymax;
  int *isGameDone_ptr;
};

void *keystrokeInstanceHandler(void* _threadArgs)
{
  args_thread *args = (args_thread*) _threadArgs;
  int fileSizeShip1,fileSizeShip2;
  int lastx=0, lasty=0;
  main_ship *ship = args->ship;

  int y = ship->coord->y;
  int x = ship->coord->x;

  char *shipFile1 = GetShip("../assets/Vaisseaux/ennemis/TestShip.txt", &fileSizeShip1);
  char *shipFile2 = GetShip("../assets/Vaisseaux/ennemis/Enemy_MotherShip.txt", &fileSizeShip2);
  printf("\033[%d;%dH", y, x);
  diplayShip(fileSizeShip1, shipFile1, y, x);
  char missile=73;
  printf("Terminal size y= %d; x= %d", args->ymax, args->xmax);
  while (1)
  {
      if (*(args->keyPressed) != 0) //Ship movement
      {
        //if (*(args->keyPressed) == 122)//Up - Z key
        //{
        //  if ((y-4)>0)
        //  {
        //  eraseShip(fileSizeShip1, shipFile1, y, x);
        //  y=y-4;
        //  printf("\033[%d;%dH", y, x);
        //  diplayShip(fileSizeShip1, shipFile1, y, x);
        //  printf("\033[%d;%dH", y, x);
        //  }
        //}
        //if (*(args->keyPressed) == 115)//Down - S key
        //{
        //  if ((y+4)<ymax)
        //  {
        //  eraseShip(fileSizeShip1, shipFile1, y, x);
        //  y=y+4;
        //  printf("\033[%d;%dH", y, x);
        //  diplayShip(fileSizeShip1, shipFile1, y, x);
        //  printf("\033[%d;%dH", y, x);
        //  }
        //}
        if (*(args->keyPressed) == 113)//Left - Q key
        {
          if ((x-4)>0)
          {
          eraseShip(fileSizeShip1, shipFile1, y, x);
          x=x-4;
          printf("\033[%d;%dH", y, x);
          diplayShip(fileSizeShip1, shipFile1, y, x);
          printf("\033[%d;%dH", y, x);
          }
        }
        if (*(args->keyPressed) == 100)//Right - D key
        {
          if ((x+4)< args->xmax)
          {
          eraseShip(fileSizeShip1, shipFile1, y, x);
          x=x+4;
          printf("\033[%d;%dH", y, x);
          diplayShip(fileSizeShip1, shipFile1, y, x);
          printf("\033[%d;%dH", y, x);        }
        }
        if (*(args->keyPressed) == 32)//Fire - Space key
        {
          for (int i = 0; i < (y -2) ; i++)
          {
              lastx = x+4;
              lasty = (y-1)-i;
              printf("\033[%d;%dH%c", lasty, lastx, 32);
              printf("\033[%d;%dH%c", lasty-1, lastx, missile);
              fflush(stdout);
              usleep(7000);
          }
        printf("\033[%d;%dH%c", lasty-1, lastx, 32);
        }
        if (*(args->keyPressed) == 27)//Quit - Escape 
        {
          *(args->isGameDone_ptr) = 1;
          return NULL;
        }
    usleep(5000);
    }
  }
  return NULL;
}

int main(void){
  char keyPressed;
  system("clear");
  printf("\e[?25l"); //hide the terminal cursor
  struct winsize w;
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
  args->ship->coord->y = ymax - 1;
  args->ship->coord->x = xmax / 2;
  args->keyPressed = &keyPressed;

  pthread_create(&thread_id, NULL, keystrokeInstanceHandler, (void*)args);
  while (1)
  {
    if (*(args->isGameDone_ptr) == 1) {
      pthread_join(thread_id, NULL);
      break;
    } 
    keyPressed=key_pressed();

  }
  system("reset");
  return 0;
}