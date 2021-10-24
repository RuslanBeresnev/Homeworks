#include "MostFrequentElement.h"
#include <stdbool.h>

#pragma warning (disable: 5045)

int partitionFinding(int array[], int startPos, int endPos)
{
    const int pivot = array[(startPos + endPos) / 2];
    while (true)
    {
        while (array[startPos] < pivot)
        {
            startPos++;
        }
        while (array[endPos] > pivot)
        {
            endPos--;
        }
        if (startPos >= endPos)
        {
            return endPos;
        }
        const int bufferValue = array[startPos];
        array[startPos] = array[endPos];
        array[endPos] = bufferValue;
        startPos++;
        endPos--;
    }
}

void quickSorting(int array[], int startPos, int endPos)
{
    if (startPos < endPos)
    {
        const int partition = partitionFinding(array, startPos, endPos);
        quickSorting(array, startPos, partition);
        quickSorting(array, partition + 1, endPos);
    }
}

int findMostFrequentElement(int array[], int length)
{
    quickSorting(array, 0, length - 1);
    int mostFrequentElement = array[0];
    int maxFrequence = 0;
    int counter = 1;
    for (int i = 1; i < length; i++)
    {
        if (array[i] == array[i - 1])
        {
            counter++;
            if (counter > maxFrequence)
            {
                maxFrequence = counter;
                mostFrequentElement = array[i - 1];
            }
        }
        else
        {
            counter = 1;
        }
    }
    return mostFrequentElement;
}