#include "MostFrequentElement.h"
#include "QuickSorting.h"
#include <stdbool.h>

#pragma warning (disable: 5045)

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