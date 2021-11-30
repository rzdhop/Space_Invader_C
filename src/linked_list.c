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
        Element *toDelete, *currentShip;
        int x, y;
        if (elementToDelete == 1)
        {
            toDelete = list->first;
            list->first = list->first->next;
        }
        else
        {
            currentShip = list->first;
            for (int i = 1; i < elementToDelete - 1; i++) //Start at 1 because the first ship is already counted with list->first the line before
            {
                currentShip = currentShip->next;
            }
            toDelete = currentShip->next;
            currentShip->next = currentShip->next->next;
        }
        y = toDelete->Y;
        x = toDelete->X;
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