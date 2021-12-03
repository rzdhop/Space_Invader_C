#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"
#include "struct_def.h"

LinkedList *initialization(linkedMalloc *list2Free)
{
    LinkedList *list = malloc(sizeof(LinkedList));
    registerFree(list2Free, list);
    enemy *firstElement = malloc(sizeof(enemy));
    firstElement->coord = malloc(sizeof(coordinate));
    firstElement->hitbox = malloc(sizeof(coordinate));
    firstElement->ID = 1;
    firstElement->coord->y = 1;
    firstElement->coord->x = 4;
    firstElement->hitbox->x = firstElement->coord->x+8;
    firstElement->hitbox->y = firstElement->coord->y+1;
    firstElement->next = NULL;
    list->top = firstElement;

    return list;
}

void addShip(LinkedList *list, int shipWidth)
{
    /* Création du nouvel élément */
    enemy *nouveau = malloc(sizeof(enemy));
    nouveau->coord = malloc(sizeof(coordinate));
    nouveau->hitbox = malloc(sizeof(coordinate));
    nouveau->ID = list->top->ID+1;
    nouveau->coord->x = list->top->coord->x+(shipWidth+1);
    nouveau->coord->y = list->top->coord->y;
    nouveau->hitbox->x = nouveau->coord->x+8;
    nouveau->hitbox->y = list->top->coord->y;

    // Insertion de l'élément au début de la list 
    nouveau->next = list->top; 
    list->top = nouveau; //la maille de debut est nouveau  
}

void removeShip(LinkedList *list, int fileSizeShip, char *shipFile, int enemyID)
{
    if(list == NULL)return;
    if (list->top != NULL)
    {
        enemy *toDelete, *current = list->top;
        if (enemyID == 1)
        {
            toDelete = list->top;
            list->top = list->top->next;
        }
        else
        {
            current = list->top;
            for (int i = 1; i < enemyID-1 ; i++) 
            {
                current = current->next;
            }
            toDelete = current->next;
            current->next = current->next->next; //remplace la maille supprimé par celle d'apres.
        }
        eraseShip(fileSizeShip, shipFile, toDelete->coord->y, toDelete->coord->x);
        free(toDelete);
    }
    
}

int displayList(LinkedList *list, int fileSizeShip, char *shipFile, char direction)
{
    if(list==NULL)return;
    int numberOfShips=0, garbageInt=0;
    enemy *current = list->top;

    while (current != NULL)
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
        diplayShip(fileSizeShip, shipFile, current->coord->y, current->coord->x, &garbageInt);
        numberOfShips++; 
        current = current->next;
    }
    return numberOfShips;
}

void eraseList(LinkedList *list, int fileSizeShip, char *shipFile)
{
    if (list == NULL)exit(EXIT_FAILURE);
    enemy *current = list->top;
    while (current != NULL)
    {
        eraseShip(fileSizeShip, shipFile, current->coord->y, current->coord->x);
        current = current->next;
    }
    printf("\n");
}

enemy* getLastOfLinkedList(LinkedList *list)
{
    enemy *enemy = list->top;
    while (enemy->next != NULL)
    {
        enemy = enemy->next;
    }
    return enemy;
}