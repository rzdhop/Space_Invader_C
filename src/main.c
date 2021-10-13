#include <stdio.h>
#include <stdlib.h>
#include "struct_def.c"


int main(void){
  int fileSizeShip1,fileSizeShip2;
  char *shipFile1 = GetShip("../assets/Vaisseaux/ennemis/TestShip.txt", &fileSizeShip1);
  char *shipFile2 = GetShip("../assets/Vaisseaux/ennemis/Enemy_MotherShip.txt", &fileSizeShip2);  
  while(1)
  {
    for (int y=0; y<50; y++)
    {
      for (int i=0; i<5; i++)
      {
        printf("\033[%dH", (y-1)+i);
        printf("\r                                                              ");
      }   
     printf("\033[%dH", y-1);
     printf("\r                                                              ");
     printf("\033[%dH", y);
     diplayShip(fileSizeShip1, shipFile1);
     usleep(100000);
     if (y>48)
     {
       for (int a=0; a<5; a++)
      {
        printf("\033[%dH", 49+a);
        printf("\r                                                              ");
      } 
     }
    }
  }
  //diplayShip(fileSizeShip2, shipFile2);

  return 0;
}