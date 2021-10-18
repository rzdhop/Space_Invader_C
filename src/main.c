#include <stdio.h>
#include <stdlib.h>
#include "struct_def.c"
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

char key_pressed()
{
struct termios oldterm, newterm;
int oldfd; char c, result = 0;
tcgetattr (STDIN_FILENO, &oldterm);
newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
oldfd = fcntl (STDIN_FILENO, F_GETFL, 0);
fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK) ;
c = getchar();
tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
fcntl (STDIN_FILENO, F_SETFL, oldfd);
if (c != EOF) {ungetc(c, stdin) ; result = getchar();}
return result;
}

int main(void){
  int fileSizeShip1,fileSizeShip2;
  int y=4; //Vertical axis 
  int x=0; //Horizontal axis
  char *shipFile1 = GetShip("../assets/Vaisseaux/ennemis/TestShip.txt", &fileSizeShip1);
  char *shipFile2 = GetShip("../assets/Vaisseaux/ennemis/Enemy_MotherShip.txt", &fileSizeShip2);  
  printf("\033[%d;%dH", y, x);
  diplayShip(fileSizeShip1, shipFile1);
  char a=0;
  printf("\e[?25l"); //hide the terminal cursor

  while (1)
  {
  a=key_pressed();
    if (a != NULL)
    {
      if (a == 122)//Up - Z key
    {
      for (int i=0; i<7;i++)
      {
        printf("\033[%d;%dH", y+i, x);
        printf("                                                  ");
      }
      y=y-4;
      printf("\033[%d;%dH", y, x);
      diplayShip(fileSizeShip1, shipFile1);
    }
    if (a == 115)//Down - S key
    {
      for (int i=0;i<7;i++)
      {
        printf("\033[%d;%dH", y+i, x);
        printf("                                                  ");
      }
      y=y+4;
      printf("\033[%d;%dH", y, x);
      diplayShip(fileSizeShip1, shipFile1);
    }
    if (a == 113)//Left - Q key
    {
      for (int i=0;i<7;i++)
      {
        printf("\033[%d;%dH", y, x+i);
        printf("                                                  ");
      }
      x=x-4;
      printf("\033[%d;%dH", y, x);
      diplayShip(fileSizeShip1, shipFile1);
    }
    if (a == 100)//Right - D key
    {
      for (int i=0;i<7;i++)
      {
        printf("\033[%d;%dH", y, x+i);
        printf("                                                  ");
      }
      x=x+4;
      printf("\033[%d;%dH", y, x);
      diplayShip(fileSizeShip1, shipFile1);
    }
    }


  }
  //diplayShip(fileSizeShip2, shipFile2);

  return 0;
}