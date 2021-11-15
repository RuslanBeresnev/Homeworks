#pragma warning (disable: 4710 5045 6011)

#include "PhoneBookList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListElement
{
    Note data;
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

bool isLast(Position* position)
{
    return position->position == NULL;
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
    if (currentPosition->position == NULL)
    {
        return currentPosition;
    }
    while (currentPosition->position->next != NULL)
    {
        Position* currentPositionCopy = currentPosition;
        currentPosition = next(currentPosition);
        deletePosition(currentPositionCopy);
    }
    return currentPosition;
}

Position* next(Position* position)
{
    if (isLast(position))
    {
        return position;
    }
    Position* newPosition = malloc(sizeof(Position));
    newPosition->position = position->position->next;
    return newPosition;
}

void addToStart(List* list, Note data)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    newElement->data = data;
    newElement->next = list->head;
    list->head = newElement;
}

void addAfter(Position* position, Note data)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    newElement->data = data;
    if (isLast(position))
    {
        return;
    }
    newElement->next = position->position->next;
    position->position->next = newElement;
}

bool deleteElementAfterPosition(Position* position)
{
    if (isLast(position) || position->position->next == NULL)
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

Note getData(Position* position)
{
    if (isLast(position))
    {
        Note empty = { 0 };
        return empty;
    }
    return position->position->data;
}

void printList(List* list)
{
    Position* position = getFirstElement(list);
    while (!isLast(position))
    {
        Note data = getData(position);
        printf("%s: %s\n", data.name, data.phoneNumber);
        Position* positionCopy = position;
        position = next(position);
        deletePosition(positionCopy);
    }
    deletePosition(position);
}

Position* getPositionByIndex(List* list, int index)
{
    Position* position = getFirstElement(list);
    for (int i = 0; i < index; i++)
    {
        Position* positionCopy = position;
        position = next(position);
        deletePosition(positionCopy);
    }
    return position;
}

void setData(Position* position, Note data)
{
    position->position->data = data;
}

bool isEmptyData(Position* position)
{
    Note data = getData(position);
    return data.name[0] == '\0' && data.phoneNumber[0] == '\0';
}