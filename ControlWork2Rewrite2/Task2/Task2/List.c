#pragma warning (disable: 4820 6011)

#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListElement
{
    char* value;
    int frequency;
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
    if (list == NULL)
    {
        return;
    }

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

void next(Position* position)
{
    if (!last(position))
    {
        position->position = position->position->next;
    }
}

void addToFront(List* list, char* value)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    newElement->value = value;
    newElement->frequency = 1;
    newElement->next = list->head;
    list->head = newElement;
}

char* getValue(Position* position)
{
    return position->position->value;
}

int getElementFrequency(Position* position)
{
    return position->position->frequency;
}

bool valueInList(List* list, char* value)
{
    if (list == NULL)
    {
        return false;
    }
    Position* position = first(list);
    while (!last(position))
    {
        if (strcmp(value, getValue(position)) == 0)
        {
            return true;
        }
        next(position);
    }
    deletePosition(position);
    return false;
}

void setFrequency(Position* position, const int frequency)
{
    position->position->frequency = frequency;
}

Position* getPositionByValue(List* list, char* value)
{
    if (!valueInList(list, value))
    {
        return NULL;
    }
    Position* position = first(list);
    while (strcmp(getValue(position), value) != 0)
    {
        next(position);
    }
    return position;
}

bool isEmpty(List* list)
{
    return list->head == NULL;
}

void printList(List* list)
{
    ListElement* position = list->head;
    while (position != NULL)
    {
        printf("%s\n", position->value);
        position = position->next;
    }
}

int getElementsCount(List* list)
{
    ListElement* position = list->head;
    int count = 0;

    while (position != NULL)
    {
        count++;
        position = position->next;
    }

    return count;
}