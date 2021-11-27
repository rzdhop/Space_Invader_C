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

void removeShip(LinkedList *list, int fileSizeShip, char *shipFile, int y, int x, int elementToDelete)
{
    if (list == NULL)
    {
        return;
    }

    if (list->first != NULL)
    {
        eraseShip(fileSizeShip, shipFile, y, x);
        Element *toDelete;
        switch (elementToDelete)
        {
        case 1:
                toDelete = list->first;
                list->first = list->first->next;
                break;
        case 2:
                toDelete = list->first->next;
                list->first->next = list->first->next->next;
                break;
        case 3:            
                toDelete = list->first->next->next;
                list->first->next->next = list->first->next->next->next;
                break;
        default:
                break;
        }
        
        free(toDelete);
    }
}

void displayList(LinkedList *list, int fileSizeShip, char *shipFile, char direction)
{
    if (list == NULL)
    {
        exit(EXIT_FAILURE);
    }

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
        current = current->next;
    }
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