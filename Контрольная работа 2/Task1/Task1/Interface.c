#pragma warning (disable: 4996 5045)

#include "List.h"

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

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
        const int countOfReadNumbers = fscanf(numbersFile, "%d", &number);
        if (countOfReadNumbers < 0)
        {
            break;
        }
        array[numbersRead] = number;
        numbersRead++;
    }
    fclose(numbersFile);
    return numbersRead;
}

void addNumbersFromArrayToList(List* list, const int numbers[], const int length)
{
    Position* position = first(list);
    for (int i = 0; i < length; i++)
    {
        if (i == 0)
        {
            addToFront(list, numbers[i]);
            Position* copyOfPosition = position;
            position = first(list);
            deletePosition(copyOfPosition);
        }
        else
        {
            addAfter(position, numbers[i]);
            next(position);
        }
    }
    deletePosition(position);
}

bool generalTestPassed(void)
{
    int numbers[100] = { 0 };
    const int inputCount = readNumbersFromFile("Test input.txt", numbers);
    List* list = createList();
    addNumbersFromArrayToList(list, numbers, inputCount);

    List* reversedList = createReversedList(list);
    const int correctArray[] = { 10, 9, 1, 5, 4, 4, 3, 1 };
    Position* position = first(reversedList);
    bool verdict = true;
    for (int i = 0; i < inputCount; i++)
    {
        if (correctArray[i] != get(position))
        {
            verdict = false;
        }
        next(position);
    }

    deletePosition(position);
    deleteList(list);
    deleteList(reversedList);
    return verdict;
}

int main(void)
{
    if (!generalTestPassed())
    {
        printf("Tests Failed ...\n");
        return 1;
    }

    setlocale(LC_ALL, "Russian");
    int numbers[100] = { 0 };
    const int inputCount = readNumbersFromFile("input.txt", numbers);
    List* list = createList();
    addNumbersFromArrayToList(list, numbers, inputCount);

    printf("Исходный список: ");
    printList(list);

    List* reversedList = createReversedList(list);
    printf("Перевёрнутый список: ");
    printList(reversedList);

    deleteList(list);
    deleteList(reversedList);
}