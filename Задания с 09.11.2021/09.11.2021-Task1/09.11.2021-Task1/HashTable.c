#pragma warning (disable: 5045)

#include "HashTable.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct HashTable
{
    List* segments[SEGMENTS_COUNT];
} HashTable;

HashTable* createHashTable(void)
{
    return calloc(1, sizeof(HashTable));
}

int hash(char* value)
{
    int result = 0;
    const int length = (int)strlen(value);
    const int simpleNumber = 3;
    for (int i = 0; i < length; i++)
    {
        result += (int)((unsigned char)value[i] * pow(simpleNumber, length - i - 1));
    }
    return result;
}

void addValue(HashTable* hashTable, char* value)
{
    const int segmentIndex = hash(value) % SEGMENTS_COUNT;
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
    for (int i = 0; i < SEGMENTS_COUNT; i++)
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
    int valuesCount = 0;
    for (int i = 0; i < SEGMENTS_COUNT; i++)
    {
        List* currentList = hashTable->segments[i];
        if (currentList == NULL)
        {
            continue;
        }
        valuesCount += getLength(currentList);
    }
    return (float)valuesCount / SEGMENTS_COUNT;
}

int getMaxSegmentLength(HashTable* hashTable)
{
    int maxSeqmentLength = 0;
    for (int i = 0; i < SEGMENTS_COUNT; i++)
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
    for (int i = 0; i < SEGMENTS_COUNT; i++)
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

List* getSegmentByIndex(HashTable* hashTable, const int index)
{
    return hashTable->segments[index];
}