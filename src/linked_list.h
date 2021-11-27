typedef struct Element Element;
struct Element
{
    int X, Y, shipID, hitbox_X, hitbox_Y;
    Element *next;
};

typedef struct LinkedList LinkedList;
struct LinkedList
{
    Element *first;
};

void eraseList(LinkedList *list, int fileSizeShip, char *shipFile);
void displayList(LinkedList *list, int fileSizeShip, char *shipFile, char direction);
void removeShip(LinkedList *list, int fileSizeShip, char *shipFile, int y, int x, int elementToDelete);
void addShip(LinkedList *list);
LinkedList *initialization();