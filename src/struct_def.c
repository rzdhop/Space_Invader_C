#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "struct_def.h"

#define bool unsigned int 
#define true 1
#define false 0


char *GetShip(char *fileName, int *fileSizePTR)
{
  FILE * ship = fopen(fileName, "r");
  
  char bufferChar;
  int fileSize= 0;

  //GET FILE SIZE
  for(int i= 0; (bufferChar = fgetc(ship)) != EOF; fileSize++){}
  
  //allocate memory to welcome fileSize number of type char * (addr retuned in malocShipFile) 
  char *malocShipFile = (char *) malloc(fileSize);

  //set fileSizePTR 
  *fileSizePTR = fileSize;

  //Init size of the buffer that contain the ship 
  char shipFile[fileSize];

  //flush File stream
  rewind(ship);

  //Get the char of the file in the tab to print the ship
  for(int i= 0; i < fileSize && (bufferChar = fgetc(ship)) != EOF; i++)
  {
    shipFile[i] = bufferChar;
  }

  //actually print the ship char per char
  fclose(ship);

  //Copy direct memory content without arithmetic
  strcpy(malocShipFile, shipFile);

  return malocShipFile;

}

int diplayShip(int fileSizeShip, char *shipFile, int y, int x)
{
int shipHeight=1;
printf("\033[%d;%dH", y, x);
  for(int i= 0, f=0; i< fileSizeShip; i++) 
  {
    if (shipFile[i] == 10)
    {
      shipHeight++;
      f++;
      printf("\n");
      printf("\033[%d;%dH", y+f, x);
      i++;
    }
    printf("%c", shipFile[i]);
  }
    printf("\n");
    return shipHeight;
} 

void eraseShip (int fileSizeShip, char *ShipFile, int y, int x)
{ 
  
  char eraserShipFile[fileSizeShip];
  printf("\033[%d;%dH", y, x);//positionne le curseur a la position actuelle du vaisseau

  //create a mask of the ship with only spaces instead of characters
  //replace each table position with ' ' if different than LF (return line)
  for(int i= 0; i< fileSizeShip; i++) 
  {
    eraserShipFile[i]=ShipFile[i];
    if (eraserShipFile[i] != 10) //we keep only the Line Feed (LF)
    {
      eraserShipFile[i] = 32;
    }
  }
  
  //write the actual table (full of ' ') to erase the ship
  for(int i= 0, f=0; i< fileSizeShip; i++) 
  {
    if (eraserShipFile[i] == 10)//LF
    {
      f++;
      printf("\n");
      printf("\033[%d;%dH", y+f, x);
      i++;
    }
    printf("%c", eraserShipFile[i]);
  }
    printf("\n");
}
linkedMalloc *_iniFreeRegister(void *addr2Free)
{
  linkedMalloc *list = malloc(sizeof(linkedMalloc));
  malloc2free *top = malloc(sizeof(malloc2free));
  top->addr = addr2Free;
  top->next = NULL;

  return list;
}
void registerFree(linkedMalloc *list, void *addr2Free)
{
  malloc2free *newAddr = malloc(sizeof(malloc2free));
  newAddr->addr = addr2Free;
  newAddr->next = list->top;
  list->top = newAddr;
}
void freeRegistered(linkedMalloc *list)
{
  malloc2free *current = list->top; 
  malloc2free *freeMe;

  while(current != NULL)
  {
    freeMe = current;
    current = current->next;
    if(freeMe->addr != NULL) free(freeMe);
  }
  free(list);
  return;
}
