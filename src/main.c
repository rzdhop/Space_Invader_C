#include <stdio.h>
#include <stdlib.h>
#include "struct_def.h"


int main(void){
  int fileSizeShip1,fileSizeShip2;
  char *shipFile1 = GetShip("../assets/vaisseaux/enemi/BadShip.txt", &fileSizeShip1);
  char *shipFile2 = GetShip("../assets/vaisseaux/enemi/Enemy_MotherShip.txt", &fileSizeShip2);
  
  diplayShip(fileSizeShip1, shipFile1);
  diplayShip(fileSizeShip2, shipFile2);

  return 0;
}