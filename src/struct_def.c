#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

  //set fileSizerPTR 
  *fileSizePTR = fileSize;

  //Init size of the buffer that contain the ship 
  char shipFile[fileSize];

  //flush File stream
  rewind(ship);

  //Get the char of the file in the tab to print the ship
  for(int i= 0; i< fileSize && (bufferChar = fgetc(ship)) != EOF; i++)
  {
    shipFile[i] = bufferChar;
  }

  //actually print the ship char per char
  fclose(ship);

  //Copy direct memory content without arithmetic
  strcpy(malocShipFile, shipFile);

  return malocShipFile;

}
void diplayShip(int fileSizeShip, char *shipFile)
{
  for(int i= 0; i< fileSizeShip; i++) printf("%c", shipFile[i]);
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