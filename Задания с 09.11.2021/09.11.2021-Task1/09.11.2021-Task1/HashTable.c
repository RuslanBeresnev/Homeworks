#include "HashTable.h"

#include <stdlib.h>
#include <string.h>

typedef struct HashTable
{
    List* segments[100];
} HashTable;

HashTable* createHashTable(void)
{
    return calloc(1, sizeof(HashTable));
}

int hash(char* value) // Поменять на полиномиальную
{
    int result = 0;
    for (int i = 0; value[i] != '\0'; i++)
        result += (int)value[i];
    return result;
}

void addValue(HashTable* hashTable, char* value)
{
    const int segmentIndex = hash(value) % 100;
    if (hashTable->segments[segmentIndex] == NULL)
    {
        hashTable->segments[segmentIndex] = createList();
    }
    if (valueInList(hashTable->segments[segmentIndex], value))
    {
        Position* position = getPositionByValue(hashTable->segments[segmentIndex], value);
        setFrequency(position, getElementFrequency(position) + 1);
        deletePosition(position);
    }
    else
    {
        addToFront(hashTable->segments[segmentIndex], value);
    }
}

int getValueFrequency(HashTable* hashTable, char* value)
{
    List* suitableList = hashTable->segments[hash(value)];
    Position* position = getPositionByValue(suitableList, value);
    if (position == NULL)
    {
        return -1;
    }
    else
    {
        const int frequency = getElementFrequency(position);
        deletePosition(position);
        return frequency;
    }
}

void deleteHashTable(HashTable* hashTable)
{
    for (int i = 0; i < 100; i++)
    {
        if (hashTable->segments[i] != NULL)
        {
            deleteList(hashTable->segments[i]);
        }
    }
    free(hashTable);
}

float getFillFactor(HashTable* hashTable)
{
    int segmentsCount = 0;
    int valuesCount = 0;
    for (int i = 0; i < 100; i++)
    {
        List* currentList = hashTable->segments[i];
        if (currentList == NULL)
        {
            continue;
        }
        segmentsCount++;

        Position* position = first(currentList);
        while (!last(position))
        {
            valuesCount++;
            next(position);
        }
        deletePosition(position);
    }
    return (float)valuesCount / segmentsCount;
}

int getMaxSegmentLength(HashTable* hashTable)
{
    int maxSeqmentLength = 0;
    for (int i = 0; i < 100; i++)
    {
        List* currentList = hashTable->segments[i];
        if (currentList == NULL)
        {
            continue;
        }
        const int length = getLength(currentList);
        if (length > maxSeqmentLength)
        {
            maxSeqmentLength = length;
        }
    }
    return maxSeqmentLength;
}

float getAverageSegmentLength(HashTable* hashTable)
{
    int sumOfLengths = 0;
    int segmentsCount = 0;
    for (int i = 0; i < 100; i++)
    {
        List* currentList = hashTable->segments[i];
        if (currentList == NULL)
        {
            continue;
        }
        sumOfLengths += getLength(currentList);
        segmentsCount++;
    }
    return (float)sumOfLengths / segmentsCount;
}