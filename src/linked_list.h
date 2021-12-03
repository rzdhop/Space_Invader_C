#include "struct_def.h"

void eraseList(LinkedList *list, int fileSizeShip, char *shipFile);
int displayList(LinkedList *list, int fileSizeShip, char *shipFile, char direction);
void removeShip(LinkedList *list, int fileSizeShip, char *shipFile, int enemyID);
void addShip(LinkedList *list, int shipWidth);
LinkedList *initialization();
enemy* getLastOfLinkedList(LinkedList *list);