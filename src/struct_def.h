char *GetShip(char *fileName, int *fileSizePTR);
int diplayShip(int fileSizeShip, char *shipFile, int y, int x);
void eraseShip (int fileSizeShip, char *shipFile, int y, int x);

typedef struct fShip fShip;
struct fShip
{
    int posX, posY;
};