#define MAX_WORDS_COUNT 1000

#pragma warning (disable: 4996 5045 6031)

#include "HashTable.h"
#include "List.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

int readWordsFromFile(const char fileName[], char* array[], const int maxCount)
{
    FILE* numbersFile = fopen(fileName, "r");
    if (numbersFile == NULL)
    {
        return -1;
    }
    int wordsRead = 0;
    while (!feof(numbersFile))
    {
        char* word = calloc(30, sizeof(char));
        fscanf_s(numbersFile, "%s", word, 29);
        array[wordsRead] = word;
        wordsRead++;

        if (wordsRead > maxCount)
        {
            break;
        }
    }
    fclose(numbersFile);
    return wordsRead;
}

bool generalTestPassed(void)
{
    char* allWords[30] = { NULL };
    readWordsFromFile("Test Text.txt", allWords, 30);

    HashTable* wordsFrequences = createHashTable(5);
    for (int i = 0; i < 30; i++)
    {
        if (allWords[i] == NULL)
        {
            break;
        }
        addValue(wordsFrequences, allWords[i]);
    }

    if (getFillFactor(wordsFrequences) < 1.1 && getMaxSegmentLength(wordsFrequences) < 3 && getAverageSegmentLength(wordsFrequences) < 2)
    {
        deleteHashTable(wordsFrequences);
        return true;
    }

    deleteHashTable(wordsFrequences);
    return false;
}

int main(void)
{
    if (!generalTestPassed())
    {
        printf("Tests Failed ...\n");
        return 1;
    }

    setlocale(LC_ALL, "Russian");

    char* allWords[MAX_WORDS_COUNT] = { NULL };
    readWordsFromFile("Text.txt", allWords, MAX_WORDS_COUNT);
    
    HashTable* wordsFrequences = createHashTable(10);
    for (int i = 0; i < MAX_WORDS_COUNT; i++)
    {
        if (allWords[i] == NULL)
        {
            break;
        }
        addValue(wordsFrequences, allWords[i]);
    }

    printf("Частоты всех слов из файла:\n");
    printWordsFrequences(wordsFrequences);
    printf("\n");

    printf("Коэффициент заполненности хэш-таблицы: %f\n", getFillFactor(wordsFrequences));
    printf("Длина максимального сегмента в хэш-таблице: %d\n", getMaxSegmentLength(wordsFrequences));
    printf("Средняя длина сегмента в хэш-таблице: %f\n", getAverageSegmentLength(wordsFrequences));
    printf("\n");
    printf("Количество сегментов в хэш-таблице: %d\n", getSegmentsCount(wordsFrequences));

    deleteHashTable(wordsFrequences);
}