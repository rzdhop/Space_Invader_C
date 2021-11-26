#pragma once

typedef struct xy_coordinate coordinate;
struct xy_coordinate
{
  int x;
  int y;
};

enum keystroke
{
  LEFT = 113, //Q
  RIGHT = 100, //D
  FIRE = 32, //SPACE
  SPAWN = 112, //P
  QUIT = 27, //ESC
};
//struct keystroke mouv = {.LEFT=113, .RIGHT=100, .FIRE=32, .SPAWN=112,  .QUIT=27};

typedef struct fireShotInstance fireInst;
struct fireShotInstance 
{
  coordinate *coord;
  int state;
  int relativePosY;
};

typedef struct enemy_data enemy;
struct enemy_data
{
  coordinate *coord;
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


struct globalEnvironnmentData //TODO
{
  int eShipCnt;
  int ymax;
  int xmax;
};

char *GetShip(char *fileName, int *fileSizePTR);
int diplayShip(int fileSizeShip, char *shipFile, int y, int x);
void eraseShip (int fileSizeShip, char *shipFile, int y, int x);

