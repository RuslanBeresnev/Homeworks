#pragma warning (disable: 4820 6011)

#include "List.h"

#include <stdio.h>
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

void addToFront(List* list, int value)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    newElement->value = value;
    newElement->next = list->head;
    list->head = newElement;
}

void addAfter(Position* position, int value)
{
    if (last(position))
    {
        return;
    }
    ListElement* newElement = calloc(1, sizeof(ListElement));
    newElement->value = value;
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

List* createReversedList(List* source)
{
    List* reversed = createList();
    Position* sourcePosition = first(source);
    Position* reversedPosition = first(reversed);
    while (!last(sourcePosition))
    {
        addToFront(reversed, get(sourcePosition));
        next(sourcePosition);
        next(reversedPosition);
    }
    deletePosition(sourcePosition);
    deletePosition(reversedPosition);
    return reversed;
}

void printList(List* list)
{
    Position* position = first(list);
    while (!last(position))
    {
        printf("%d ", get(position));
        next(position);
    }
    printf("\n");
    deletePosition(position);
}