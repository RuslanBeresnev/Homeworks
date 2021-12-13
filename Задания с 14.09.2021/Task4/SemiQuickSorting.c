#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

void semiQuickSorting(int array[], int arrayLength)
{
    int leftCursor = 1;
    int rightCursor = arrayLength - 1;
    const int pivot = array[0];
    while (leftCursor < rightCursor)
    {
        while (array[leftCursor] < pivot && leftCursor < arrayLength)
        {
            leftCursor++;
        }
        while (array[rightCursor] >= pivot && rightCursor > 0)
        {
            rightCursor--;
        }
        if (leftCursor < rightCursor)
        {
            const int bufferValue = array[leftCursor];
            array[leftCursor] = array[rightCursor];
            array[rightCursor] = bufferValue;
            leftCursor++;
            rightCursor--;
        }
    }
}

bool arrayOfThreeElementsCase()
{
    int testedArray[3] = { 2, 4, -6 };
    semiQuickSorting(testedArray, 3);
    return testedArray[1] == -6 && testedArray[2] == 4;
}

bool sameElementsCase()
{
    int testedArray[4] = { 5, 5, 5, 5 };
    semiQuickSorting(testedArray, 4);
    return testedArray[1] == 5 && testedArray[2] == 5 && testedArray[3] == 5;
}

bool generalTest()
{
    return arrayOfThreeElementsCase() && sameElementsCase();
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

    printf("Enter count of elements in array:\n");
    int count = 0;
    const int input = scanf("%d", &count);
    if (input != 1)
    {
        printf("You entered not a number ...\n");
        return 1;
    }
    int array[100] = { 0 };
    srand(time(NULL));
    printf("Original array: ");
    for (int i = 0; i < count; i++)
    {
        array[i] = rand() % 1000 + 1;
        printf("%d ", array[i]);
    }
    semiQuickSorting(array, count);
    printf("\nSorted array: ");
    for (int i = 0; i < count; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}