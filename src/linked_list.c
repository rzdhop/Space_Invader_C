#include <stdlib.h>
#include "linked_list.h"

LinkedList *initialization()
{
    LinkedList *list = malloc(sizeof(*list));
    Element *element = malloc(sizeof(*element));

    if (list == NULL || element == NULL)
    {
        exit(EXIT_FAILURE);
    }

    element->Y = 1;
    element->X = 4;
    element->shipID = 1;
    element->hitbox_X = element->X+8;
    element->hitbox_Y = element->Y+1;
    element->next = NULL;
    list->first = element;

    return list;
}

void addShip(LinkedList *list)
{
    /* Création du nouvel élément */
    Element *nouveau = malloc(sizeof(*nouveau));
    if (list == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->X = list->first->X + 10;
    nouveau->Y = list->first->Y;
    nouveau->shipID = list->first->shipID+1;
    nouveau->hitbox_X = list->first->X+10;
    nouveau->hitbox_Y = list->first->Y;

    /* Insertion de l'élément au début de la list */
    nouveau->next = list->first;
    list->first = nouveau;
}

void removeShip(LinkedList *list, int fileSizeShip, char *shipFile, int elementToDelete)
{
    if (list == NULL)
    {
        return;
    }

    if (list->first != NULL)
    {
        int x, y;
        Element *toDelete;
        switch (elementToDelete)
        {
        case 1:
                toDelete = list->first;
                x=toDelete->X;
                y=toDelete->Y;
                list->first = list->first->next;
                break;
        case 2:
                toDelete = list->first->next;
                x=toDelete->X;
                y=toDelete->Y;
                list->first->next = list->first->next->next;
                break;
        case 3:            
                toDelete = list->first->next->next;
                x=toDelete->X;
                y=toDelete->Y;
                list->first->next->next = list->first->next->next->next;
                break;
        case 4:            
                toDelete = list->first->next->next->next;
                x=toDelete->X;
                y=toDelete->Y;
                list->first->next->next->next = list->first->next->next->next->next;
                break;
        case 5:            
                toDelete = list->first->next->next->next->next;
                x=toDelete->X;
                y=toDelete->Y;
                list->first->next->next->next->next = list->first->next->next->next->next->next->next;
                break;
        case 6:            
                toDelete = list->first->next->next->next->next->next;
                x=toDelete->X;
                y=toDelete->Y;
                list->first->next->next->next->next->next = list->first->next->next->next->next->next->next->next;
                break;
        case 7:            
                toDelete = list->first->next->next->next->next->next->next;
                x=toDelete->X;
                y=toDelete->Y;
                list->first->next->next->next->next->next->next = list->first->next->next->next->next->next->next->next->next;
                break;
        case 8:            
                toDelete = list->first->next->next->next->next->next->next->next;
                x=toDelete->X;
                y=toDelete->Y;
                list->first->next->next->next->next->next->next->next = list->first->next->next->next->next->next->next->next->next->next;
                break;
        default:
                break;
        }
        eraseShip(fileSizeShip, shipFile, y, x);
        free(toDelete);
    }
}

int displayList(LinkedList *list, int fileSizeShip, char *shipFile, char direction)
{
    if (list == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int numberOfShips=0;
    Element *current = list->first;
    while (current != NULL)
    {
        if (direction == 'l')
        {
            current->X-=2;
        }
        else
        {
        current->X+=2;
        }
        diplayShip(fileSizeShip, shipFile, current->Y, current->X);
        numberOfShips++;
        current = current->next;
    }
    return numberOfShips;
    printf("\n");
}

void eraseList(LinkedList *list, int fileSizeShip, char *shipFile)
{
    if (list == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Element *current = list->first;
    while (current != NULL)
    {
        eraseShip(fileSizeShip, shipFile, current->Y, current->X);
        current = current->next;
    }
    printf("\n");
}