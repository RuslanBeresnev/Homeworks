#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Массив с 100_000 случайными элементами сортируется пузырьком за 30.104 секунды, а сортировкой подсчётом - за 0.003 секунды
// Таким образом, сортировка подсчётом быстрее сортировки пузырьком в 10_000 раз

void bubbleSort(int array[], int length)
{
    for (int i = length - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (array[j] > array[i])
            {
                const int bufferValue = array[j];
                array[j] = array[i];
                array[i] = bufferValue;
            }
        }
    }
}

int byCountSort(int array[], int length)
{
    int maxElement = array[0];
    int minElement = array[0];
    for (int i = 0; i < length; i++)
    {
        if (array[i] > maxElement)
        {
            maxElement = array[i];
        }
        if (array[i] < minElement)
        {
            minElement = array[i];
        }
    }
    const int minMaxValuesDelta = maxElement - minElement + 1;
    int *countsOfEachElement = calloc(minMaxValuesDelta, sizeof(int));
    if (countsOfEachElement == NULL)
    {
        printf("Sorry, we ran out of memory for your huge array ... And why do you need so much data ..........\n");
        return 1;
    }
    for (int i = 0; i < length; i++)
    {
        countsOfEachElement[array[i] - minElement]++;
    }
    int counter = 0;
    for (int i = minElement; i <= maxElement; i++)
    {
        for (int j = 0; j < countsOfEachElement[i - minElement]; j++)
        {
            array[counter] = i;
            counter++;
        }
    }
    free(countsOfEachElement);
    return 0;
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

bool positiveElementsTest()
{
    int testArrayOne[5] = { 5, 5, 3, 2, 4 };
    const int correctArrayOne[5] = { 2, 3, 4, 5, 5 };
    int testArrayTwo[5] = { 6, 6, 3, 10, 55 };
    const int correctArrayTwo[5] = { 3, 6, 6, 10, 55 };
    bubbleSort(testArrayOne, 5);
    byCountSort(testArrayTwo, 5);
    return comparingTwoIntArrays(testArrayOne, correctArrayOne, 5) && comparingTwoIntArrays(testArrayTwo, correctArrayTwo, 5);
}

bool negativeElementsTest()
{
    int testArrayOne[5] = { -3, 4,-3, 2, 10 };
    const int correctArrayOne[5] = { -3, -3, 2, 4, 10 };
    int testArrayTwo[5] = { -10, -3, -1, 0, -10 };
    const int correctArrayTwo[5] = { -10, -10, -3, -1, 0 };
    bubbleSort(testArrayOne, 5);
    byCountSort(testArrayTwo, 5);
    return comparingTwoIntArrays(testArrayOne, correctArrayOne, 5) && comparingTwoIntArrays(testArrayTwo, correctArrayTwo, 5);
}

bool arraysWithLargeScatter()
{
    int testArrayOne[5] = { -1005, 555, -156, 2, 1566 };
    const int correctArrayOne[5] = { -1005, -156, 2, 555, 1566 };
    int testArrayTwo[5] = { -10567, 9876, -1, 0, -1900 };
    const int correctArrayTwo[5] = { -10567, -1900, -1, 0, 9876 };
    bubbleSort(testArrayOne, 5);
    byCountSort(testArrayTwo, 5);
    return comparingTwoIntArrays(testArrayOne, correctArrayOne, 5) && comparingTwoIntArrays(testArrayTwo, correctArrayTwo, 5);
}

bool generalTest()
{
    return positiveElementsTest() && negativeElementsTest() && arraysWithLargeScatter();
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
    int arrayCopy[100] = { 0 };
    for (int i = 0; i < count; i++)
    {
        int number = 0;
        const int numberInput = scanf("%d", &number);
        if (numberInput != 1)
        {
            printf("Something went wrong ...\n");
            return 1;
        }
        array[i] = number;
        arrayCopy[i] = number;
    }

    const int errorCode = byCountSort(array, count);
    if (errorCode != 0)
    {
        printf("Something went wrong ...\n");
        return 1;
    }
    bubbleSort(arrayCopy, count);

    printf("Bubble sorted array: ");
    for (int i = 0; i < count; i++)
    {
        printf("%d ", arrayCopy[i]);
    }
    printf("\nSorted by count array: ");
    for (int i = 0; i < count; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}