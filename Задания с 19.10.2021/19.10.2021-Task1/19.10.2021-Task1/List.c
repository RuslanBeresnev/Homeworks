#pragma warning (disable: 6011)

#include "List.h"
#include <stdlib.h>

typedef struct ListElement
{
    int value;
    struct ListElement* next;
} ListElement;

typedef struct List
{
    ListElement* head;
} List;

typedef struct Position
{
    ListElement* position;
} Position;

void deletePosition(Position* position)
{
    free(position);
}

List* createList(void)
{
    return calloc(1, sizeof(List));
}

void deleteList(List* list)
{
    ListElement* position = list->head;
    while (position != NULL)
    {
        list->head = list->head->next;
        free(position);
        position = list->head;
    }
    free(list);
}

Position* first(List* list)
{
    Position* positionFirst = malloc(sizeof(Position));
    positionFirst->position = list->head;
    return positionFirst;
}

bool last(Position* position)
{
    return position->position == NULL;
}

Position* next(Position* position)
{
    if (last(position))
    {
        position->position = NULL;
        return position;
    }
    Position* newPosition = malloc(sizeof(Position));
    newPosition->position = position->position->next;
    return newPosition;
}

void addToStart(List* list, int value)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    newElement->value = value;
    newElement->next = list->head;
    list->head = newElement;
}

void addAfter(Position* position, int value)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    newElement->value = value;
    if (last(position))
    {
        return;
    }
    newElement->next = position->position->next;
    position->position->next = newElement;
}

bool deleteElementAfterPosition(Position* position)
{
    if (last(position) || next(position)->position == NULL)
    {
        return false;
    }
    ListElement* elementForDelete = position->position->next;
    position->position->next = position->position->next->next;
    free(elementForDelete);
    return true;
}

bool deleteFirstElement(List* list)
{
    if (list->head != NULL)
    {
        ListElement* firstElement = list->head;
        list->head = list->head->next;
        free(firstElement);
        return true;
    }
    return false;
}

int get(Position* position)
{
    return position->position->value;
}