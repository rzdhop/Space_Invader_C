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

  int eShipCnt=1, counter=0;
  int j1=0, j2=0, j3=0, j4=0, j5=0, j6=0;
  int fire1=0, fire2=0, fire3=0, fire4=0, fire5=0, fire6=0;
  int t1, u1, t2, u2, t3, u3, t4, u4, t5, u5, t6, u6;
  char a=0;
  int shipHeight=0;

  char *shipFile1 = GetShip("../assets/Vaisseaux/ennemis/TestShip.txt", &fileSizeShip1);
  char *shipFile2 = GetShip("../assets/Vaisseaux/ennemis/Enemy_MotherShip.txt", &fileSizeShip2);
  fShip myShip;
  fShip eShip;
  eShip.posY=1;
  eShip.posX= (args->xmax)/2;
  myShip.posY = (args->ymax)-1;
  myShip.posX= (args->xmax)/2;
  char direction = 'r';
  printf("\033[%d;%dH", myShip.posY, myShip.posX);
  shipHeight = diplayShip(fileSizeShip1, shipFile1, myShip.posY, myShip.posX);
  char missile=73;

  int totalShips=0;

    LinkedList *shipList = initialization();

    addShip(shipList);
    addShip(shipList);
    addShip(shipList);
    addShip(shipList);
    addShip(shipList);
    addShip(shipList);
    addShip(shipList);

  //printf("Terminal size y= %d; x= %d", args->ymax, args->xmax);
  while (1)
  {

    if (shipList->first != NULL)
    {
      counter++;
      if (counter % 8 == 0)
      {
        if (eShipCnt + 137 > args->xmax)
        {
          direction = 'l';
        }
        if (eShipCnt < 1)
        {
          direction = 'r';
        }

        if (direction == 'r')
        {
          eShipCnt++;
          eraseList(shipList, fileSizeShip1, shipFile1);
          totalShips = displayList(shipList, fileSizeShip1, shipFile1, direction);
        }

        if (direction == 'l')
        {
          eShipCnt--;
          eraseList(shipList, fileSizeShip1, shipFile1);
          totalShips = displayList(shipList, fileSizeShip1, shipFile1, direction);
        }
      }
    }

    if (fire1 == 1)
    {
      int shipWidth = 8;
      int elToDel = 1;
      fireMissile(missile, t1 - j1, u1);
      j1++;
      if ((t1 - j1) < 15 && shipList->first != NULL) //To do - instead of 15 put the height of the last enemy ship
      {
        Element *test;
        test = shipList->first;
        while (test != NULL)
        {
          if (u1 > test->X && u1 < test->X + 8 && (t1 - j1) < (test->Y + shipHeight))
          {
            removeShip(shipList, fileSizeShip1, shipFile1, elToDel);
            fire1 = 0;
            j1 = 0;
            break;
          }
          elToDel++;
          test = test->next;
        }
      }
      if (j1 > (args->ymax) - shipHeight + 2)
      {
        printf("\033[%d;%dH ", t1 - j1, u1);
        fire1 = 0;
        j1 = 0;
      }
    }

    if (fire2 == 1)
    {
      int shipWidth = 8;
      int elToDel = 1;
      fireMissile(missile, t2 - j2, u2);
      j2++;
      if ((t2 - j2) < 15 && shipList->first != NULL) //To do - instead of 15 put the height of the last enemy ship
      {
        Element *test;
        test = shipList->first;
        while (test != NULL)
        {
          if (u2 > test->X && u2 < test->X + 8 && (t2 - j2) < (test->Y + shipHeight))
          {
            removeShip(shipList, fileSizeShip1, shipFile1, elToDel);
            fire2 = 0;
            j2 = 0;
            break;
          }
          elToDel++;
          test = test->next;
        }
      }
      if (j2 > (args->ymax) - shipHeight + 2)
      {
        printf("\033[%d;%dH ", t2 - j2, u2);
        fire2 = 0;
        j2 = 0;
      }
    }
    if (fire3 == 1)
    {
      int shipWidth = 8;
      int elToDel = 1;
      fireMissile(missile, t3 - j3, u3);
      j3++;
      if ((t3 - j3) < 15 && shipList->first != NULL) //To do - instead of 15 put the height of the last enemy ship
      {
        Element *test;
        test = shipList->first;
        while (test != NULL)
        {
          if (u3 > test->X && u3 < test->X + 8 && (t3 - j3) < (test->Y + shipHeight))
          {
            removeShip(shipList, fileSizeShip1, shipFile1, elToDel);
            fire3 = 0;
            j3 = 0;
            break;
          }
          elToDel++;
          test = test->next;
        }
      }
      if (j3 > (args->ymax) - shipHeight + 2)
      {
        printf("\033[%d;%dH ", t3 - j3, u3);
        fire3 = 0;
        j3 = 0;
      }
    }
    if (fire4 == 1)
    {
      int shipWidth = 8;
      int elToDel = 1;
      fireMissile(missile, t4 - j4, u4);
      j4++;
      if ((t4 - j4) < 15 && shipList->first != NULL) //To do - instead of 15 put the height of the last enemy ship
      {
        Element *test;
        test = shipList->first;
        while (test != NULL)
        {
          if (u4 > test->X && u4 < test->X + 8 && (t4 - j4) < (test->Y + shipHeight))
          {
            removeShip(shipList, fileSizeShip1, shipFile1, elToDel);
            fire4 = 0;
            j4 = 0;
            break;
          }
          elToDel++;
          test = test->next;
        }
      }
      if (j4 > (args->ymax) - shipHeight + 2)
      {
        printf("\033[%d;%dH ", t4 - j4, u4);
        fire4 = 0;
        j4 = 0;
      }
    }
    if (fire5 == 1)
    {
      int shipWidth = 8;
      int elToDel = 1;
      fireMissile(missile, t5 - j5, u5);
      j5++;
      if ((t5 - j5) < 15 && shipList->first != NULL) //To do - instead of 15 put the height of the last enemy ship
      {
        Element *test;
        test = shipList->first;
        while (test != NULL)
        {
          if (u5 > test->X && u5 < test->X + 8 && (t5 - j5) < (test->Y + shipHeight))
          {
            removeShip(shipList, fileSizeShip1, shipFile1, elToDel);
            fire5 = 0;
            j5 = 0;
            break;
          }
          elToDel++;
          test = test->next;
        }
      }
      if (j5 > (args->ymax) - shipHeight + 2)
      {
        printf("\033[%d;%dH ", t5 - j5, u5);
        fire5 = 0;
        j5 = 0;
      }
    }
    if (fire6 == 1)
    {
      int shipWidth = 8;
      int elToDel = 1;
      fireMissile(missile, t6 - j6, u6);
      j6++;
      if ((t6 - j6) < 15 && shipList->first != NULL) //To do - instead of 15 put the height of the last enemy ship
      {
        Element *test;
        test = shipList->first;
        while (test != NULL)
        {
          if (u6 > test->X && u6 < test->X + 8 && (t6 - j6) < (test->Y + shipHeight))
          {
            removeShip(shipList, fileSizeShip1, shipFile1, elToDel);
            fire6 = 0;
            j6 = 0;
            break;
          }
          elToDel++;
          test = test->next;
        }
      }
      if (j6 > (args->ymax) - shipHeight + 2)
      {
        printf("\033[%d;%dH ", t6 - j6, u6);
        fire6 = 0;
        j6 = 0;
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
        if (a == 'p')
        {
          removeShip(shipList, fileSizeShip1, shipFile1, 2);
        }

        if (a == 'm')
        {
          eraseList(shipList, fileSizeShip1, shipFile1);
        }

        if (a == 113)//Left - Q key
        {
          if ((myShip.posX-4)>0)  //Prevent moving over terminal limit
          {
          eraseShip(fileSizeShip1, shipFile1, myShip.posY, myShip.posX);
          myShip.posX=myShip.posX-4;
          diplayShip(fileSizeShip1, shipFile1, myShip.posY, myShip.posX);
          continue;
          }
        }
        if (a == 100)//Right - D key
        {
          if ((myShip.posX+4)< args->xmax) //Prevent moving over terminal limit
          {
          eraseShip(fileSizeShip1, shipFile1, myShip.posY, myShip.posX);
          myShip.posX=myShip.posX+4;
          diplayShip(fileSizeShip1, shipFile1, myShip.posY, myShip.posX);
          continue;
          }
        }
        if (a == 32)//Fire - Space key
        {
          if (fire1==0)
          {
            t1=myShip.posY-1;
            u1=myShip.posX+4;
            fire1=1;
            continue;
          }
          if (fire2==0)
          {
            t2=myShip.posY-1;
            u2=myShip.posX+4;
            fire2=1;
            continue;
          }
          if (fire3==0)
          {
          t3=myShip.posY-1;
          u3=myShip.posX+4;
          fire3=1;
          continue;
          }
          if (fire4==0)
          {
          t4=myShip.posY-1;
          u4=myShip.posX+4;
          fire4=1;
          continue;
          }
          if (fire5==0)
          {
          t5=myShip.posY-1;
          u5=myShip.posX+4;
          fire5=1;
          continue;
          }
          if (fire6==0)
          {
          t6=myShip.posY-1;
          u6=myShip.posX+4;
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