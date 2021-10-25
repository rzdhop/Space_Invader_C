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
  int fileSizeShip1,fileSizeShip2;
  int y=0; //Vertical axis 
  int x=0; //Horizontal axis
  char *shipFile1 = GetShip("../assets/Vaisseaux/ennemis/TestShip.txt", &fileSizeShip1);
  char *shipFile2 = GetShip("../assets/Vaisseaux/ennemis/Enemy_MotherShip.txt", &fileSizeShip2);  
  printf("\033[%d;%dH", y, x);
  diplayShip(fileSizeShip1, shipFile1, y, x);
  char a=0;
  char missile=73;
  int j=0;
  int fire=0;
  int t, u;
  printf("\e[?25l"); //hide the terminal cursor

  while (1)
  {
  if (fire==1)
  {
    fireMissile(missile, t+j, u);
    j++;
    if (j>50)
    {
      fire=0;
      j=0;
    }
  }
    a=key_pressed();
    if (a != 0) //Ship movement
    {
        if (a == 122)//Up - Z key
      {
        eraseShip(fileSizeShip1, shipFile1, y, x);
        y=y-4;
        printf("\033[%d;%dH", y, x);
        diplayShip(fileSizeShip1, shipFile1, y, x);
        printf("\033[%d;%dH", y, x);
      }
      if (a == 115)//Down - S key
      {
        eraseShip(fileSizeShip1, shipFile1, y, x);
        y=y+4;
        printf("\033[%d;%dH", y, x);
        diplayShip(fileSizeShip1, shipFile1, y, x);
        printf("\033[%d;%dH", y, x);
      }
      if (a == 113)//Left - Q key
      {
        eraseShip(fileSizeShip1, shipFile1, y, x);
        x=x-4;
        printf("\033[%d;%dH", y, x);
        diplayShip(fileSizeShip1, shipFile1, y, x);
        printf("\033[%d;%dH", y, x);
      }
      if (a == 100)//Right - D key
      {
        eraseShip(fileSizeShip1, shipFile1, y, x);
        x=x+4;
        printf("\033[%d;%dH", y, x);
        diplayShip(fileSizeShip1, shipFile1, y, x);
        printf("\033[%d;%dH", y, x);
      }
      if (a == 32)//Fire missile - Space key
      {
        if (fire==0)
        {
        t=y;
        u=x;
        t=t+5;
        u=u+4;
        fire=1;
        }       
      }
    }
  }
  //diplayShip(fileSizeShip2, shipFile2);

  return 0;
}
