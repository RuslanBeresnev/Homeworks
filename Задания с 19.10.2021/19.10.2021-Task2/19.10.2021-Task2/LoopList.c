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
    return newLoopList;
}

void deletePosition(Position* position)
{
    free(position);
}

Position* copyPosition(Position* position)
{
    Position* copyOfPosition = calloc(1, sizeof(Position));
    copyOfPosition->position = position->position;
    return copyOfPosition;
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
        next(currentPosition);
    }
    return currentPosition;
}

bool isLast(List* list, Position* position)
{
    Position* lastElement = getLastElement(list);
    bool verdict = position->position == lastElement->position;
    deletePosition(lastElement);
    return verdict;
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
    while (position != list->head)
    {
        ListElement* copyOfPosition = position;
        position = position->next;
        free(copyOfPosition);
    }
    free(position);
    free(list);
}

void next(Position* position)
{
    position->position = position->position->next;
}

int getNumber(Position* position)
{
    return position->position->number;
}

void addAfter(List* list, Position* position)
{
    if (position->position == NULL)
    {
        position->position = calloc(1, sizeof(ListElement));
        position->position->number = 1;
        position->position->next = position->position;
        list->head = position->position;
        return;
    }
    ListElement* newElement = malloc(sizeof(ListElement));
    newElement->number = position->position->number + 1;
    newElement->next = position->position->next;
    position->position->next = newElement;
}