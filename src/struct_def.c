#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

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

void diplayShip(int fileSizeShip, char *shipFile, int y, int x)
{
  int f=0;
  for(int i= 0; i< fileSizeShip; i++) 
  {
    if (shipFile[i] == 10)
    {
      f++;
      printf("\n");
      printf("\033[%d;%dH", y+f, x);
      i++;
    }
    printf("%c", shipFile[i]);
  }
    printf("\n");
} 

void eraseShip (int fileSizeShip, char *ShipFile, int y, int x)
{ 
  char eraserShipFile[fileSizeShip];
  printf("\033[%d;%dH", y, x);
  for(int i= 0; i< fileSizeShip; i++) //create a mask of the ship with only spaces instead of characters
  {
    eraserShipFile[i]=ShipFile[i];
    if (eraserShipFile[i] != 10) //we keep only the Line Feed (LF)
    {
      eraserShipFile[i] = 32;
    }
  }
 int f=0;
  for(int i= 0; i< fileSizeShip; i++) 
  {
    if (eraserShipFile[i] == 10)
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

struct EnvData
{
    unsigned int terminalSize;
    unsigned int difficulty;
};

typedef struct Ship
{
    unsigned int posX, posY;
    char direction;
    unsigned int life;
    bool state; 
    bool isFriendly; 
    struct Ship *nextShip;

};