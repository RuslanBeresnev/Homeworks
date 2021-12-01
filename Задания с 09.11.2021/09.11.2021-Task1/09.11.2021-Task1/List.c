#pragma warning (disable: 4820 6011)

#include "List.h"
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

Position* copyPosition(Position* position)
{
    Position* copyOfPosition = calloc(1, sizeof(Position));
    copyOfPosition->position = position->position;
    return copyOfPosition;
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

void addAfter(Position* position, char* value)
{
    if (last(position))
    {
        return;
    }
    ListElement* newElement = calloc(1, sizeof(ListElement));
    newElement->value = value;
    newElement->frequency = 1;
    newElement->next = position->position->next;
    position->position->next = newElement;
}

bool deleteElementAfterPosition(Position* position)
{
    if (last(position) || position->position->next == NULL)
    {
        return false;
    }
    ListElement* elementForDelete = position->position->next;
    position->position->next = position->position->next->next;
    free(elementForDelete->value);
    free(elementForDelete);
    return true;
}

bool deleteFirstElement(List* list)
{
    if (list->head != NULL)
    {
        ListElement* firstElement = list->head;
        list->head = list->head->next;
        free(firstElement->value);
        free(firstElement);
        return true;
    }
    return false;
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

int getLength(List* list)
{
    int length = 0;
    Position* position = first(list);
    while (!last(position))
    {
        length++;
        next(position);
    }
    free(position);
    return length;
}