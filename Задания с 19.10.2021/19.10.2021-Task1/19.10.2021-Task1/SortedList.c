#pragma warning (disable: 4996 4710)

#include "List.h"

#include <stdio.h>

 int main(void)
{
    List* myList = createList();
    addToStart(myList, 1);
    addToStart(myList, 2);
    Position* positionAfterTwo = first(myList);
    addToStart(myList, 3);
    addAfter(positionAfterTwo, 4);
    Position* position = first(myList);
    while (!last(position))
    {
        printf("%d ", get(position));
        position = next(position);
    }
    deleteList(myList);
    deletePosition(position);
    deletePosition(positionAfterTwo);
}