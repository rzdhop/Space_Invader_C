#include <stdio.h>
#include <stdlib.h>
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

void fireMissile(char missile, int y, int x)
{      
        printf("\033[%d;%dH ", y, x);  
        printf("\033[%d;%dH%c", y-1, x, missile);  
        fflush(stdout);
}