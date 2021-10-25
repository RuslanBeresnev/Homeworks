#include "QuickSorting.h"
#include <stdbool.h>

#pragma warning (disable: 5045)

int partitionFinding(int array[], int startPosition, int endPosition)
{
    const int pivot = array[(startPosition + endPosition) / 2];
    while (true)
    {
        while (array[startPosition] < pivot)
        {
            startPosition++;
        }
        while (array[endPosition] > pivot)
        {
            endPosition--;
        }
        if (startPosition >= endPosition)
        {
            return endPosition;
        }
        const int bufferValue = array[startPosition];
        array[startPosition] = array[endPosition];
        array[endPosition] = bufferValue;
        startPosition++;
        endPosition--;
    }
}

void quickSorting(int array[], int startPosition, int endPosition)
{
    if (startPosition < endPosition)
    {
        const int partition = partitionFinding(array, startPosition, endPosition);
        quickSorting(array, startPosition, partition);
        quickSorting(array, partition + 1, endPosition);
    }
}