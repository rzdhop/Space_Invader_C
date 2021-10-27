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

typedef struct args_struct_thread args_thread;
struct args_struct_thread
{
    int y;
    int x;
    char missile;
    char *a;
};

void *printinga(void* _threadArgs)
{   
  args_thread *args = (args_thread*) _threadArgs;
  int fileSizeShip1,fileSizeShip2;
  int y=1; //Vertical axis 
  int x=2; //Horizontal axis
  char *shipFile1 = GetShip("../assets/Vaisseaux/ennemis/TestShip.txt", &fileSizeShip1);
  char *shipFile2 = GetShip("../assets/Vaisseaux/ennemis/Enemy_MotherShip.txt", &fileSizeShip2);  
  printf("\033[%d;%dH", y, x);
  diplayShip(fileSizeShip1, shipFile1, y, x);
  char missile=73;
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int ymax=w.ws_row-4;
  int xmax=w.ws_col-7;
    while (1)
    {
      printf("%c", *(args->a));
      if (args->a != 0) //Ship movement
      {
          if (*(args->a) == 122)//Up - Z key
        {
          if ((y-4)>0)
          {
          eraseShip(fileSizeShip1, shipFile1, y, x);
          y=y-4;
          printf("\033[%d;%dH", y, x);
          diplayShip(fileSizeShip1, shipFile1, y, x);
          printf("\033[%d;%dH", y, x);
          }
        }
        if (*(args->a) == 115)//Down - S key
        {
          if ((y+4)<ymax)
          {
          eraseShip(fileSizeShip1, shipFile1, y, x);
          y=y+4;
          printf("\033[%d;%dH", y, x);
          diplayShip(fileSizeShip1, shipFile1, y, x);
          printf("\033[%d;%dH", y, x);
          }
        }
        if (*(args->a) == 113)//Left - Q key
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
        if (*(args->a) == 100)//Right - D key
        {
          if ((x+4)<xmax)
           {
          eraseShip(fileSizeShip1, shipFile1, y, x);
          x=x+4;
          printf("\033[%d;%dH", y, x);
          diplayShip(fileSizeShip1, shipFile1, y, x);
          printf("\033[%d;%dH", y, x);        }
        }
        if (*(args->a) == 32)//Fire - Space key
        {
          for (int i = 0; i < 50; i++)
          {
              printf("\033[%d;%dH    ", y+i, x);  
              printf("\033[%d;%dH%c", y+i+1, x, missile);  
              fflush(stdout);
              usleep(7000);
          }
        }
    }
  }
  return NULL;
}

int main(void){
  char *a;
  system("clear");
  printf("\e[?25l"); //hide the terminal cursor
  pthread_t thread_id[2];
  args_thread *args = (args_thread*)malloc(sizeof(args_thread));
  args->a = a;
  pthread_create(&thread_id[0], NULL, printinga, (void *)args);
  while (1)
  {
    *a=key_pressed();
  }
  
  return 0;
}
