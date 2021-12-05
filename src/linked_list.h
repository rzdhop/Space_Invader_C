#include "struct_def.h"

void eraseList(LinkedList *list, int fileSizeShip, char *shipFile);
int displayList(LinkedList *list, int fileSizeShip, char *shipFile, char direction);
void removeShip(LinkedList *list, int fileSizeShip, char *shipFile, int enemyID);
void addShip(LinkedList *list, int shipWidth);
LinkedList *initialization(linkedMalloc *list2Free, int shipWidth, int shipHeight);
enemy* getLastOfLinkedList(LinkedList *list, int *numberOfEnemiesAlive);
enemy* getShipByID(LinkedList *list, int shipID);