#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void insertionSort(int array[], int startPos, int endPos)
{
    for (int i = startPos; i <= endPos; i++)
    {
        const int itemToInsert = array[i];
        int j = i - 1;
        while (j >= startPos && array[j] > itemToInsert)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = itemToInsert;
    }
}

int partitionFind(int array[], int startPos, int endPos)
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

void smartQuickSorting(int array[], int startPos, int endPos)
{
    if (endPos - startPos + 1 < 10)
    {
        insertionSort(array, startPos, endPos);
        return;
    }
    const int partition = partitionFind(array, startPos, endPos);
    smartQuickSorting(array, startPos, partition);
    smartQuickSorting(array, partition + 1, endPos);
}

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

bool comparingTwoIntArrays(int arrayOne[], int arrayTwo[], int totalLength)
{
    for (int i = 0; i < totalLength; i++)
    {
        if (arrayOne[i] != arrayTwo[i])
        {
            return false;
        }
    }
    return true;
}

bool smallArrayCase()
{
    int testedArray[6] = { 10, -10, -7, 6, 0, 0 };
    int correctArray[6] = { -10, -7, 0, 0, 6, 10 };
    smartQuickSorting(testedArray, 0, 5);
    return comparingTwoIntArrays(testedArray, correctArray, 6);
}

bool largeArrayCase()
{
    int testedArray[15] = {-105, -106, -7, -8, 0, 0, 10, 55, 107, 88, -909, 1000, 1, 9, 9 };
    int correctArray[15] = { -909, -106, -105, -8, -7, 0, 0, 1, 9, 9, 10, 55, 88, 107, 1000 };
    smartQuickSorting(testedArray, 0, 14);
    return comparingTwoIntArrays(testedArray, correctArray, 15);
}

bool sameElementsCase()
{
    int testedArray[10] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
    int correctArray[10] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
    smartQuickSorting(testedArray, 0, 9);
    return comparingTwoIntArrays(testedArray, correctArray, 10);
}

bool oneElementArray()
{
    int testedArray[1] = { 3 };
    smartQuickSorting(testedArray, 0, 0);
    return testedArray[0] == 3;
}

bool generalTest()
{
    return smallArrayCase() && largeArrayCase() && sameElementsCase() && oneElementArray();
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

    int count = 0;
    printf("Enter count of numbers in array:\n");
    const int countInput = scanf("%d", &count);
    if (countInput != 1)
    {
        printf("Something went wrong ...\n");
        return 1;
    }
    if (count <= 0)
    {
        return 0;
    }
    printf("Enter numbers for array:\n");
    int array[100] = { 0 };

    const int errorCode = numbersArrayInput(array, count);
    if (errorCode != 0)
    {
        printf("Something went wrong ...\n");
        return 1;
    }
    smartQuickSorting(array, 0, count - 1);
    printf("Quick sorted array: ");
    numbersArrayOutput(array, count);
}