#pragma warning (disable: 6001 6011)

#include "LoopList.h"
#include <stdlib.h>

typedef struct ListElement
{
    int number;
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

List* createLoopList(void)
{
    List* newLoopList = calloc(1, sizeof(List));
    newLoopList->head = calloc(1, sizeof(ListElement));
    newLoopList->head->number = 1;
    newLoopList->head->next = newLoopList->head;
    return newLoopList;
}

void deletePosition(Position* position)
{
    free(position);
}

Position* getFirstElement(List* list)
{
    Position* positionFirst = malloc(sizeof(Position));
    positionFirst->position = list->head;
    return positionFirst;
}

Position* getLastElement(List* list)
{
    Position* currentPosition = calloc(1, sizeof(Position));
    currentPosition->position = list->head;
    while (currentPosition->position->next != list->head)
    {
        Position* currentPositionCopy = currentPosition;
        currentPosition = next(currentPosition);
        deletePosition(currentPositionCopy);
    }
    return currentPosition;
}

bool isLast(List* list, Position* position)
{
    return position->position == getLastElement(list)->position;
}

void deleteAfter(List* list, Position* position)
{
    if (isLast(list, position))
    {
        list->head = position->position->next->next;
    }
    ListElement* elementForDelete = position->position->next;
    position->position->next = position->position->next->next;
    free(elementForDelete);
}

bool oneElementLoopList(List* list)
{
    return list->head == list->head->next;
}

void deleteLoopList(List* list)
{
    ListElement* position = list->head->next;
    ListElement* oldHead = list->head;
    while (position != oldHead)
    {
        free(position);
        position = position->next;
    }
    free(position);
    free(list);
}

Position* next(Position* position)
{
    Position* newPosition = malloc(sizeof(Position));
    newPosition->position = position->position->next;
    return newPosition;
}

int getNumber(Position* position)
{
    return position->position->number;
}

void addAfter(Position* position)
{
    ListElement* newElement = malloc(sizeof(ListElement));
    newElement->number = position->position->number + 1;
    newElement->next = position->position->next;
    position->position->next = newElement;
}