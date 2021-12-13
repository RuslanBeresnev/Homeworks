#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX_RANDOM_VALUE 1000

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

int binarySearch(int requiredNumber, int array[], int length)
{
    int low = 0;
    int high = length - 1;
    while (low <= high)
    {
        const int middle = (low + high) / 2;
        if (requiredNumber < array[middle])
        {
            high = middle - 1;
        }
        else if (requiredNumber > array[middle])
        {
            low = middle + 1;
        }
        else
        {
            return middle;
        }
    }
    return -1;
}

void randomNumbersArrayFilling(int array[], int countOfNumbers, int upperBound)
{
    for (int i = 0; i < countOfNumbers; i++)
    {
        array[i] = rand() % upperBound;
    }
}

void numbersArrayOutput(int array[], int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

bool standardCase()
{
    int testedArray[6] = { 1, 4, 5, 5, 10, 11 };
    return binarySearch(5, testedArray, 6) > -1 && binarySearch(-100, testedArray, 6) == -1;
}

bool oneElementArrayCase()
{
    int testedArray[1] = { 1 };
    return binarySearch(1, testedArray, 1) > -1 && binarySearch(-1, testedArray, 1) == -1;
}

bool generalTest()
{
    return standardCase() && oneElementArrayCase();
}

int main(int argc, char* argv[])
{
    if (strcmp(argv[1], "1") == 0)
    {
        if (generalTest())
        {
            printf("Tests Passed!\n");
            return 0;
        }
        printf("Tests Failed ...\n");
        return 1;
    }

    srand((unsigned)time(NULL));
    printf("Enter count of numbers in array: ");
    int arrayLength = 0;
    const int arrayLengthInput = scanf("%d", &arrayLength);
    if (arrayLengthInput != 1)
    {
        printf("We are amazed at your ignorance of numbers ...........\n");
        return 1;
    }
    printf("Enter the count of numbers to search: ");
    int searchedNumbersCount = 0;
    const int searchedNumbersCountInput = scanf("%d", &searchedNumbersCount);
    if (searchedNumbersCountInput != 1)
    {
        printf("We are amazed at your ignorance of numbers ...........\n");
        return 1;
    }
    int* numbersArray = calloc(arrayLength, sizeof(int));
    int* searchedNumbersArray = calloc(searchedNumbersCount, sizeof(int));

    randomNumbersArrayFilling(numbersArray, arrayLength, MAX_RANDOM_VALUE);
    randomNumbersArrayFilling(searchedNumbersArray, searchedNumbersCount, MAX_RANDOM_VALUE);
    quickSorting(numbersArray, 0, arrayLength - 1);

    printf("\n");
    printf("Original numbers array: ");
    numbersArrayOutput(numbersArray, arrayLength);
    printf("Searched numbers array: ");
    numbersArrayOutput(searchedNumbersArray, searchedNumbersCount);
    printf("\n");

    for (int i = 0; i < searchedNumbersCount; i++)
    {
        if (binarySearch(searchedNumbersArray[i], numbersArray, arrayLength) > -1)
        {
            printf("Number %d found\n", searchedNumbersArray[i]);
        }
        else
        {
            printf("Number %d not found\n", searchedNumbersArray[i]);
        }
    }

    free(numbersArray);
    free(searchedNumbersArray);
}