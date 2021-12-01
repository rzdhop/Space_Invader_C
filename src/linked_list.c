#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"
#include "struct_def.h"

LinkedList *initialization()
{
    LinkedList *list = malloc(sizeof(LinkedList));
    enemy *firstElement = malloc(sizeof(enemy));
    firstElement->coord = malloc(sizeof(coordinate));
    firstElement->hitbox = malloc(sizeof(coordinate));

    firstElement->coord->y = 1;
    firstElement->coord->x = 4;
    firstElement->enemyID = 1;
    firstElement->hitbox->x = firstElement->coord->x+8;
    firstElement->hitbox->y = firstElement->coord->y+1;
    firstElement->next = NULL;
    list->maille = firstElement;

    return list;
}

void addShip(LinkedList *list)
{
    /* Création du nouvel élément */
    enemy *nouveau = malloc(sizeof(enemy));
    nouveau->coord = malloc(sizeof(coordinate));
    nouveau->hitbox = malloc(sizeof(coordinate));
    
    nouveau->coord->x = list->maille->coord->x+10;
    nouveau->coord->y = list->maille->coord->y;
    nouveau->enemyID = list->maille->enemyID+1;
    nouveau->hitbox->x = nouveau->coord->x+8;
    nouveau->hitbox->y = list->maille->coord->y;

    // Insertion de l'élément au début de la list 
    nouveau->next = list->maille; //Le prochain de nouveau est l'ancienne maille actuel
    list->maille = nouveau; //la maille actuel est nouveau 
}

void removeShip(LinkedList *list, int fileSizeShip, char *shipFile, int enemyID)
{
    enemy *toDelete, *current = list->maille;

    while (current != NULL)
    {
        if(current->enemyID == enemyID)
        {
            toDelete = current;
            break;
        }
        current = current->next;
    }
    
    eraseShip(fileSizeShip, shipFile, toDelete->coord->x, toDelete->coord->y);
    toDelete->state = 0;
}

int displayList(LinkedList *list, int fileSizeShip, char *shipFile, char direction)
{
    int numberOfShips=0;
    enemy *current = list->maille;

    while (current != NULL)
    {
        if(current->state)
        {
            if (direction == 'l')
            {
                current->coord->x -= 2;
                current->hitbox->x -= 2;
            }
            else
            {
                current->coord->x += 2;
                current->hitbox->x += 2;
            }
            diplayShip(fileSizeShip, shipFile, current->coord->y, current->coord->x);
        }
        numberOfShips++; 
        current = current->next;
    }
    return numberOfShips;
    printf("\n");
}

void eraseList(LinkedList *list, int fileSizeShip, char *shipFile)
{
    enemy *current = list->maille;
    while (current != NULL)
    {
        eraseShip(fileSizeShip, shipFile, current->coord->y, current->coord->x);
        current = current->next;
    }
    printf("\n");
}