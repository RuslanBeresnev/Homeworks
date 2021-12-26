#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

void bubbleSort(int array[], const int count)
{
    bool noSwap;

    for (int i = count - 1; i >= 0; i--)
    {
        noSwap = true;
        for (int j = 0; j < i; j++)
        {
            if (array[j] > array[j + 1])
            {
                const int temporary = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temporary;
                noSwap = 0;
            }
        }

        if (noSwap == 1)
            break;
    }
}

int selectNumbersWithEvenIndex(const int source[], int destination[], const int sourceCount)
{
    int position = 0;
    for (int i = 0; i < sourceCount; i++)
    {
        if (i % 2 == 0)
        {
            destination[position] = source[i];
            position++;
        }
    }
    return position;
}

void insertNumbersToEvenPositions(const int numbers[], int destination[], const int numbersCount)
{
    int numbersInserted = 0;
    int destinationPosition = 0;
    while (numbersInserted < numbersCount)
    {
        if (destinationPosition % 2 == 0)
        {
            destination[destinationPosition] = numbers[numbersInserted];
            numbersInserted++;
        }
        destinationPosition++;
    }
}

void printNumbers(const int array[], const int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%d ", array[i]);
    }
}

bool compareTwoArrays(int firstArray[], int secondArray[], const int count)
{
    for (int i = 0; i < count; i++)
    {
        if (firstArray[i] != secondArray[i])
        {
            return false;
        }
    }
    return true;
}

bool standardTestPassed(void)
{
    int testedArray[5] = { 5, 4, 3, 2, 1 };
    const int correctArray[5] = { 1, 4, 3, 2, 5 };
    int numbersWithEvenIndex[5] = { 0 };
    const int countOfEvenIndexes = selectNumbersWithEvenIndex(testedArray, numbersWithEvenIndex, 5);
    bubbleSort(numbersWithEvenIndex, countOfEvenIndexes);
    insertNumbersToEvenPositions(numbersWithEvenIndex, testedArray, countOfEvenIndexes);
    return compareTwoArrays(testedArray, correctArray, 5);
}

bool sameNumbersTestPassed(void)
{
    int testedArray[5] = { 1, 1, 1, 1, 1 };
    const int correctArray[5] = { 1, 1, 1, 1, 1 };
    int numbersWithEvenIndex[5] = { 0 };
    const int countOfEvenIndexes = selectNumbersWithEvenIndex(testedArray, numbersWithEvenIndex, 5);
    bubbleSort(numbersWithEvenIndex, countOfEvenIndexes);
    insertNumbersToEvenPositions(numbersWithEvenIndex, testedArray, countOfEvenIndexes);
    return compareTwoArrays(testedArray, correctArray, 5);
}

bool oneElementArrayTestPassed(void)
{
    int testedArray[1] = { 1 };
    const int correctArray[1] = { 1 };
    int numbersWithEvenIndex[1] = { 0 };
    const int countOfEvenIndexes = selectNumbersWithEvenIndex(testedArray, numbersWithEvenIndex, 1);
    bubbleSort(numbersWithEvenIndex, countOfEvenIndexes);
    insertNumbersToEvenPositions(numbersWithEvenIndex, testedArray, countOfEvenIndexes);
    return compareTwoArrays(testedArray, correctArray, 1);
}

bool generalTestPassed(void)
{
    return standardTestPassed() && sameNumbersTestPassed() && oneElementArrayTestPassed();
}

int main(void)
{
    if (!generalTestPassed())
    {
        printf("Tests Failed ...\n");
        return 1;
    }

    setlocale(LC_ALL, "Russian");
    printf("Введите количество чисел: ");
    int count = 0;
    const int successfulCountInput = scanf("%d", &count);
    if (successfulCountInput != 1)
    {
        printf("Введены некорректные данные ...\n");
        return 1;
    }

    printf("Введите числа через пробел: ");
    int numbers[100] = { 0 };
    int currentNumber = 0;
    for (int i = 0; i < count; i++)
    {
        const int successfulNumberInput = scanf("%d", &currentNumber);
        numbers[i] = currentNumber;
        if (successfulNumberInput != 1)
        {
            printf("Введены некорректные данные ...\n");
            return 1;
        }
    }

    int numbersWithEvenIndex[100] = { 0 };
    const int countOfEvenIndexes = selectNumbersWithEvenIndex(numbers, numbersWithEvenIndex, count);
    bubbleSort(numbersWithEvenIndex, countOfEvenIndexes);
    insertNumbersToEvenPositions(numbersWithEvenIndex, numbers, countOfEvenIndexes);
    printf("Отсортированный по чётным индексам массив: ");
    printNumbers(numbers, count);
    printf("\n");
}