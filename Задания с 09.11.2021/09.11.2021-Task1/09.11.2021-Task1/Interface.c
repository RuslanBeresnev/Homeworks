#pragma warning (disable: 4996 6031)

#include "HashTable.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

int readWordsFromFile(const char fileName[], char* array[])
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
        fscanf(numbersFile, "%s", word);
        array[wordsRead] = word;
        wordsRead++;
    }
    fclose(numbersFile);
    return wordsRead;
}

int main(void)
{
    setlocale(LC_ALL, "Russian");

    char* allWords[1000] = { NULL };
    readWordsFromFile("text.txt", allWords);
    
    HashTable* wordsFrequences = createHashTable();
    for (int i = 0; i < 1000; i++)
    {
        if (allWords[i] == NULL)
        {
            break;
        }
        addValue(wordsFrequences, allWords[i]);
    }
    printf("Частоты всех слов из файла:\n");
    for (int i = 0; i < 1000; i++)
    {
        if (allWords[i] == NULL)
        {
            break;
        }
        printf("%s: %d\n", allWords[i], getValueFrequency(wordsFrequences, allWords[i]));
    }

    printf("\n");
    printf("Коэффициент заполненности хэш-таблицы: %f\n", getFillFactor(wordsFrequences));
    printf("Длина максимального сегмента в хэш-таблице: %d\n", getMaxSegmentLength(wordsFrequences));
    printf("Средняя длина сегмента в хэш-таблице: %f\n", getAverageSegmentLength(wordsFrequences));

    free(wordsFrequences);
}