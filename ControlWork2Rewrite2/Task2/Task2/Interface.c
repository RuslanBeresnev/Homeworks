#define MAX_STRINGS_COUNT 1000

#pragma warning (disable: 4996 5045 6011 6031 6387)

#include "HashTable.h"
#include "List.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

void destroyLinefeedCharacter(char string[])
{
    int position = 0;
    while (true)
    {
        if (string[position] == '\n')
        {
            string[position] = '\0';
            break;
        }
        if (string[position] == '\0')
        {
            break;
        }

        position++;
    }
}

int readStringsFromFile(const char fileName[], char* array[], const int maxCount)
{
    FILE* file = fopen(fileName, "r");
    if (file == NULL)
    {
        return -1;
    }
    int stringsRead = 0;
    while (!feof(file))
    {
        char* string = calloc(100, sizeof(char));
        fgets(string, maxCount, file);
        destroyLinefeedCharacter(string);

        array[stringsRead] = string;
        stringsRead++;

        if (stringsRead > maxCount)
        {
            break;
        }
    }
    fclose(file);
    return stringsRead;
}

bool generalTestPassed(void)
{
    char* strings[MAX_STRINGS_COUNT] = { NULL };
    readStringsFromFile("Test Input.txt", strings, MAX_STRINGS_COUNT);

    HashTable* stringsFrequences = createHashTable(10);
    for (int i = 0; i < MAX_STRINGS_COUNT; i++)
    {
        if (strings[i] == NULL)
        {
            break;
        }
        addValue(stringsFrequences, strings[i]);
    }

    List* resultList = getListOfValues(stringsFrequences);
    bool verdict = false;
    if (valueInList(resultList, "abc abc") && valueInList(resultList, "def def") && getElementsCount(resultList) == 2)
    {
        verdict = true;
    }

    deleteList(resultList);
    deleteHashTable(stringsFrequences);

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

    char* strings[MAX_STRINGS_COUNT] = { NULL };
    readStringsFromFile("Input.txt", strings, MAX_STRINGS_COUNT);
    
    HashTable* stringsFrequences = createHashTable(10);
    for (int i = 0; i < MAX_STRINGS_COUNT; i++)
    {
        if (strings[i] == NULL)
        {
            break;
        }
        addValue(stringsFrequences, strings[i]);
    }

    List* resultList = getListOfValues(stringsFrequences);
    if (isEmpty(resultList))
    {
        printf("В списке нет строк ...\n");
    }
    else
    {
        printf("Все строки списка:\n");
        printf("\n");
        printList(resultList);
    }

    deleteList(resultList);
    deleteHashTable(stringsFrequences);
}