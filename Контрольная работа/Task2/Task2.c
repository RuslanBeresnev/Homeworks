#include <stdio.h>
#include <stdbool.h>

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

void selectionSort(int array[], int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        int minElementIndex = i;
        for (int j = i + 1; j < length; j++)
        {
            if (array[j] < array[minElementIndex])
            {
                minElementIndex = j;
            }
        }
        const int bufferValue = array[i];
        array[i] = array[minElementIndex];
        array[minElementIndex] = bufferValue;
    }
}

bool compareTwoIntArrays(int arrayOne[], int arrayTwo[], int totalLength)
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

bool standardCase()
{
    const int testedArray[3] = { 4, 1, 2 };
    const int correctArray[3] = { 1, 2, 4 };
    selectionSort(testedArray, 3);
    return compareTwoIntArrays(testedArray, correctArray, 3);
}

bool oneElementArrayCase()
{
    const int testedArray[1] = { 1 };
    const int correctArray[1] = { 1 };
    selectionSort(testedArray, 1);
    return compareTwoIntArrays(testedArray, correctArray, 1);
}

bool generalTest()
{
    return standardCase() && oneElementArrayCase();
}

int main()
{
    if (!generalTest())
    {
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
    int array[10] = { 0 };
    const int errorCode = numbersArrayInput(array, count);
    if (errorCode != 0)
    {
        printf("Something went wrong ...\n");
        return 1;
    }

    selectionSort(array, count);

    numbersArrayOutput(array, count);
    printf("\n");
}