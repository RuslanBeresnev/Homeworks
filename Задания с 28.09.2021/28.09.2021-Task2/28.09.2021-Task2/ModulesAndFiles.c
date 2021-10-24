﻿#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MostFrequentElement.h"

#pragma warning (disable: 4996 5045)

int readNumbersFromFile(const char fileName[], int array[])
{
    FILE* numbersFile = fopen(fileName, "r");
    if (numbersFile == NULL)
    {
        return -1;
    }
    int numbersRead = 0;
    while (!feof(numbersFile))
    {
        int number = 0;
        const int countOfReadedNumbers = fscanf(numbersFile, "%d", &number);
        if (countOfReadedNumbers < 0)
        {
            break;
        }
        array[numbersRead] = number;
        numbersRead++;
    }
    fclose(numbersFile);
    return numbersRead;
}

bool generalTestPassed(void)
{
    int testedArray[100] = { 0 };
    const int countOfNumbers = readNumbersFromFile("test_input.txt", testedArray);
    int correctResult[1] = { 0 };
    readNumbersFromFile("correct_result.txt", correctResult);
    return findMostFrequentElement(testedArray, countOfNumbers) == correctResult[0];
}

int main(void)
{
    if (!generalTestPassed())
    {
        printf("Tests Failed ...\n");
        return 1;
    }

    int array[100] = { 0 };
    const int countOfNumbers = readNumbersFromFile("input.txt", array);
    if (countOfNumbers == 0)
    {
        printf("Ouch ...\n");
        return 1;
    }

    const int mostFrequentElement = findMostFrequentElement(array, countOfNumbers);
    printf("Most frequent element in array is: %d\n", mostFrequentElement);
}