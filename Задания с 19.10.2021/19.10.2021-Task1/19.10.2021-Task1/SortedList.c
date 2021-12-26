#include "SortedList.h"

#include <stdio.h>
#include <stdbool.h>

void addNumberToList(List* list, const int number)
{
    Position* position = first(list);
    if (last(position))
    {
        addToFront(list, number);
        return;
    }
    if (get(position) >= number)
    {
        addToFront(list, number);
        deletePosition(position);
        return;
    }
    Position* nextPosition = copyPosition(position);
    next(nextPosition);
    while (!last(nextPosition) && get(nextPosition) < number)
    {
        next(position);
        next(nextPosition);
    }
    addAfter(position, number);
    deletePosition(nextPosition);
    deletePosition(position);
}

bool removeNumberFromList(List* list, const int index)
{
    if (index == 0)
    {
        return deleteFirstElement(list);
    }
    Position* position = first(list);
    for (int i = 0; i < index - 1; i++)
    {
        if (last(position))
        {
            break;
        }
        next(position);
    }
    const bool successfulRemove = deleteElementAfterPosition(position);
    deletePosition(position);
    return successfulRemove;
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