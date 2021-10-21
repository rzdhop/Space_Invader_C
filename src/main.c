#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

extern char *GetShip(char *fileName, int *fileSizePTR);
extern void diplayShip(int fileSizeShip, char *shipFile, int y, int x);
void eraseShip (int fileSizeShip, char *shipFile, int y, int x);

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
  system("clear");
  int fileSizeShip1,fileSizeShip2;
  int y=0; //Vertical axis 
  int x=0; //Horizontal axis
  char *shipFile1 = GetShip("../assets/Vaisseaux/ennemis/TestShip.txt", &fileSizeShip1);
  char *shipFile2 = GetShip("../assets/Vaisseaux/ennemis/Enemy_MotherShip.txt", &fileSizeShip2);  
  printf("\033[%d;%dH", y, x);
  diplayShip(fileSizeShip1, shipFile1, y, x);
  char a=0;
  printf("\e[?25l"); //hide the terminal cursor

  while (1)
  {
  a=key_pressed();
    if (a != 0)
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
    }
  }
  //diplayShip(fileSizeShip2, shipFile2);

  return 0;
}