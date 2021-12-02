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
  enemy *next;
  coordinate *hitbox;
  coordinate *coord;
  int ID;
};

typedef struct main_friendly_ship main_ship;
struct main_friendly_ship 
{
  coordinate *coord; 
  int state;
  int life;
};

typedef struct malloc2free malloc2free;
struct malloc2free
{
  malloc2free *next;
  void *addr;
};

typedef struct linkedMalloc linkedMalloc;
struct linkedMalloc
{
  malloc2free *top;
};


typedef struct args_struct_thread args_thread;
struct args_struct_thread
{
  linkedMalloc *list2free;
  main_ship *ship;
  char *keyPressed;
  int xmax;
  int ymax;
  int *isGameDone_ptr;
  
};

typedef struct LinkedList LinkedList;
struct LinkedList
{
  enemy *top;
};

char *GetShip(char *fileName, int *fileSizePTR);
int diplayShip(int fileSizeShip, char *shipFile, int y, int x);
void eraseShip (int fileSizeShip, char *shipFile, int y, int x);
linkedMalloc *_iniFreeRegister(void *addr2Free);
void registerFree(linkedMalloc *list, void *addr2Free);
void freeRegistered(linkedMalloc *list);

