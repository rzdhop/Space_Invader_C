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
  int xmax;
  int ymax;
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

  int j1=0, j2=0, j3=0, j4=0, j5=0, j6=0;
  int fire1=0, fire2=0, fire3=0, fire4=0, fire5=0, fire6=0;
  int t1, u1, t2, u2, t3, u3, t4, u4, t5, u5, t6, u6;
  char a=0;

  char *shipFile1 = GetShip("../assets/Vaisseaux/ennemis/TestShip.txt", &fileSizeShip1);
  char *shipFile2 = GetShip("../assets/Vaisseaux/ennemis/Enemy_MotherShip.txt", &fileSizeShip2);
  printf("\033[%d;%dH", y, x);
  diplayShip(fileSizeShip1, shipFile1, y, x);
  char missile=73;
  printf("Terminal size y= %d; x= %d", args->ymax, args->xmax);
  while (1)
  {
        if (fire1==1)
    {
        printf("\033[%d;%dH    ", t1-j1, u1);  
        printf("\033[%d;%dH%c", t1-j1-1, u1, missile);  
        fflush(stdout);
      j1++;
      if (j1>50)
      {
        printf("\033[%d;%dH   ", t1-j1, u1);  
        printf("\033[%d;%dH", y, x);         //Return to origin to avoid keeping a letter at the top of the terminal when missile dissapears
        fire1=0;
        j1=0;
      }    
    }
      if (fire2==1)
    {
        printf("\033[%d;%dH    ", t2-j2, u2);  
        printf("\033[%d;%dH%c", t2-j2-1, u2, missile);  
        fflush(stdout);
      j2++;
      if (j2>50)
      {
        printf("\033[%d;%dH   ", t2-j2, u2);  
        printf("\033[%d;%dH", y, x);         //Return to origin to avoid keeping a letter at the top of the terminal when missile dissapears
        fire2=0;
        j2=0;
      }    
    }  
      if (fire3==1)
    {
        printf("\033[%d;%dH    ", t3-j3, u3);  
        printf("\033[%d;%dH%c", t3-j3-1, u3, missile);  
        fflush(stdout);
        j3++;
      if (j3>50)
      {
        printf("\033[%d;%dH   ", t3-j3, u3);  
        printf("\033[%d;%dH", y, x);       //Return to origin to avoid keeping a letter at the top of the terminal when missile dissapears
        fire3=0;
        j3=0;
      }
    }
      if (fire4==1)
    {
        printf("\033[%d;%dH    ", t4-j4, u4);  
        printf("\033[%d;%dH%c", t4-j4-1, u4, missile);  
        fflush(stdout);
        j4++;
      if (j4>50)
      {
        printf("\033[%d;%dH   ", t4-j4, u4);  
        printf("\033[%d;%dH", y, x);       //Return to origin to avoid keeping a letter at the top of the terminal when missile dissapears
        fire4=0;
        j4=0;
      }
    }
      if (fire5==1)
    {
        printf("\033[%d;%dH    ", t5-j5, u5);  
        printf("\033[%d;%dH%c", t5-j5-1, u5, missile);  
        fflush(stdout);
        j5++;
      if (j5>50)
      {
        printf("\033[%d;%dH   ", t5-j5, u5);  
        printf("\033[%d;%dH", y, x);       //Return to origin to avoid keeping a letter at the top of the terminal when missile dissapears
        fire5=0;
        j5=0;
      }    
    }
    if (fire6==1)
    {
        printf("\033[%d;%dH    ", t6-j6, u6);  
        printf("\033[%d;%dH%c", t6-j6-1, u6, missile);  
        fflush(stdout);
        j6++;
      if (j6>50)
      {
        printf("\033[%d;%dH   ", t6-j6, u6);  
        printf("\033[%d;%dH", y, x);       //Return to origin to avoid keeping a letter at the top of the terminal when missile dissapears
        fire6=0;
        j6=0;
      }
    }    
    usleep(18000); //Missile speed - increase to lower speed / decrease to higher speed
    a=*(args->keyPressed);
      if (a != 0) //Ship movement
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
        if (a == 113)//Left - Q key
        {
          if ((x-4)>0)
          {
          eraseShip(fileSizeShip1, shipFile1, y, x);
          x=x-4;
          printf("\033[%d;%dH", y, x);
          diplayShip(fileSizeShip1, shipFile1, y, x);
          printf("\033[%d;%dH", y, x);
          continue;
          }
          else     //avoid characters to print and erase the ship when reaching terminal limit
          {
            printf("\033[%d;%dH", y, x);
            diplayShip(fileSizeShip1, shipFile1, y, x);
            printf("\033[%d;%dH", y, x);
            continue;
          }
        }
        if (a == 100)//Right - D key
        {
          if ((x+4)< args->xmax)
          {
          eraseShip(fileSizeShip1, shipFile1, y, x);
          x=x+4;
          printf("\033[%d;%dH", y, x);
          diplayShip(fileSizeShip1, shipFile1, y, x);
          printf("\033[%d;%dH", y, x);
          continue;
          }
          else   //avoid characters to print and erase the ship when reaching terminal limit
          {
            printf("\033[%d;%dH", y, x);
            diplayShip(fileSizeShip1, shipFile1, y, x);
            printf("\033[%d;%dH", y, x);
            continue;
          }
        }
        if (a == 32)//Fire - Space key
        {
          if (fire1==0)
          {
            t1=y-1;
            u1=x+4;
            fire1=1;
            continue;
          } 
          if (fire2==0)
          {
            t2=y-1;
            u2=x+4;
            fire2=1; 
            continue;
          }
          if (fire3==0)
          {
          t3=y-1;
          u3=x+4;
          fire3=1; 
          continue;
          }
          if (fire4==0)
          {
          t4=y-1;
          u4=x+4;
          fire4=1; 
          continue;
          }
          if (fire5==0)
          {
          t5=y-1;
          u5=x+4;
          fire5=1; 
          continue;
          } 
          if (fire6==0)
          {
          t6=y-1;
          u6=x+4;
          fire6=1; 
          continue;
          } 
        }

        if (a == 27)//Quit - Escape 
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
    usleep(20000);
  }
  system("reset");
  return 0;
}