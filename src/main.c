#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "struct_def.h"
#include "key_pressed.h"

int main(void){
  system("clear");
  //init Thread 
  int fileSizeShip1,fileSizeShip2;
  int y=1; //Vertical axis 
  int x=0; //Horizontal axis
  int ymax=48;
  int xmax=192;
  char *shipFile1 = GetShip("../assets/Vaisseaux/ennemis/TestShip.txt", &fileSizeShip1);
  char *shipFile2 = GetShip("../assets/Vaisseaux/ennemis/Enemy_MotherShip.txt", &fileSizeShip2);  
  printf("\033[%d;%dH", y, x);
  diplayShip(fileSizeShip1, shipFile1, y, x);
  char a=0;
  char missile=73;
  int j1=0, j2=0, j3=0;
  int fire1=0, fire2=0, fire3=0;
  int t1, u1, t2, u2, t3, u3;
  printf("\e[?25l"); //hide the terminal cursor

  while (1)
  {
    if (fire1==1)
    {
      fireMissile(missile, t1+j1, u1);
      j1++;
      if (j1>50)
      {
        printf("\033[%d;%dH   ", t1+j1, u1);  
        fire1=0;
        j1=0;
      }    
    }
        if (fire2==1)
    {
      fireMissile(missile, t2+j2, u2);
      j2++;
      if (j2>50)
      {
        printf("\033[%d;%dH   ", t2+j2, u2);  
        fire2=0;
        j2=0;
      }    
    }  
      if (fire3==1)
    {
      fireMissile(missile, t3+j3, u3);
      j3++;
      if (j3>50)
      {
        printf("\033[%d;%dH   ", t3+j3, u3);  
        fire3=0;
        j3=0;
      }    
    }
    a=key_pressed();
    if (a != 0) //Ship movement
    {
        if (a == 122)//Up - Z key
      {
        if ((y-4)>1)
        {
        eraseShip(fileSizeShip1, shipFile1, y, x);
        y=y-4;
        printf("\033[%d;%dH", y, x);
        diplayShip(fileSizeShip1, shipFile1, y, x);
        printf("\033[%d;%dH", y, x);
        }
      }
      if (a == 115)//Down - S key
      {
        if ((y+4)<50)
        {
        eraseShip(fileSizeShip1, shipFile1, y, x);
        y=y+4;
        printf("\033[%d;%dH", y, x);
        diplayShip(fileSizeShip1, shipFile1, y, x);
        printf("\033[%d;%dH", y, x);
        }
      }
      if (a == 113)//Left - Q key
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
      if (a == 100)//Right - D key
      {
        if ((x+4)<xmax)
        {
        eraseShip(fileSizeShip1, shipFile1, y, x);
        x=x+4;
        printf("\033[%d;%dH", y, x);
        diplayShip(fileSizeShip1, shipFile1, y, x);
        printf("\033[%d;%dH", y, x);        }
      }
      if (a == 32)//Fire missile - Space key
      {
        if (fire1==0)
        {
          t1=y+5;
          u1=x+4;
          fire1=1;
          continue;
        }  
        if (fire2==0)
        {
          t2=y+5;
          u2=x+4;
          fire2=1; 
          continue;
        }
        if (fire3==0)
        {
          t3=y+5;
          u3=x+4;
          fire3=1; 
          continue;
        }
      }
    }
  }
  //diplayShip(fileSizeShip2, shipFile2);

  return 0;
}
