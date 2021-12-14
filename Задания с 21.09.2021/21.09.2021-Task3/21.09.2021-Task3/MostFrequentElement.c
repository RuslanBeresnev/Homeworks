#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#pragma warning (disable: 4996 5045)

int numbersArrayInput(int array[], int count)
{
    for (int i = 0; i < count; i++)
    {
        int number = 0;
        const int numberInput = scanf("%d", &number);
        if (numberInput != 1)
        {
            return 1;
        }
        array[i] = number;
    }
    return 0;
}

void numbersArrayOutput(int array[], int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

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

bool standardCase(void)
{
    int testedArray[8] = { 7, 1, 3, 1, 5, 3, 5, 5 };
    return findMostFrequentElement(testedArray, 8) == 5;
}

bool oneElementArrayCase(void)
{
    int testedArray[1] = { 1 };
    return findMostFrequentElement(testedArray, 1) == 1;
}

bool hugeSpreadOfValuesCase(void)
{
    int testedArray[5] = { -1000000, 2000000, 2000000, 0, 2000000 };
    return findMostFrequentElement(testedArray, 5) == 2000000;
}

bool generalTest(void)
{
    return standardCase() && oneElementArrayCase() && hugeSpreadOfValuesCase();
}

int main(int argc, char* argv[])
{
    if (strcmp(argv[1], "1") == 0)
    {
        if (generalTest())
        {
            printf("21.09.2021-Task3.sln: Tests Passed!\n");
            return 0;
        }
        printf("21.09.2021-Task3.sln: Tests Failed ...\n");
        return 1;
    }

    printf("Enter count of elements: ");
    int count = 0;
    const int countInput = scanf("%d", &count);
    if (countInput != 1)
    {
        printf("Ouch ...\n");
        return 1;
    }
    printf("Enter elements of array:\n");
    int* array = calloc(count, sizeof(int));
    if (array == NULL)
    {
        printf("Something went wrong ...\n");
        return 1;
    }
    const int errorCode = numbersArrayInput(array, count);
    if (errorCode != 0)
    {
        printf("Ouch ...\n");
        return 1;
    }

    const int mostFrequentElement = findMostFrequentElement(array, count);
    printf("Most frequent element in array is: %d\n", mostFrequentElement);

    free(array);
}