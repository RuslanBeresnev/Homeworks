#pragma warning (disable: 4090 4820 5045 6011)

#include "HashTable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashTable
{
    List** segments;
    int size;
} HashTable;

HashTable* createHashTable(const int size)
{
    HashTable* newHashTable = calloc(1, sizeof(HashTable));
    newHashTable->segments = calloc(size, sizeof(List*));
    newHashTable->size = size;
    return newHashTable;
}

int hash(char* value)
{
    if (value == NULL)
    {
        return 0;
    }

    int result = (unsigned char)value[0];
    const int length = (int)strlen(value);
    const int simpleNumber = 3;
    for (int i = 1; i < length; i++)
    {
        result = abs((int)(result * simpleNumber + (unsigned char)value[i]));
    }
    return result;
}

float getFillFactor(HashTable* hashTable)
{
    int valuesCount = 0;
    for (int i = 0; i < hashTable->size; i++)
    {
        List* currentList = hashTable->segments[i];
        if (currentList == NULL)
        {
            continue;
        }
        valuesCount += getElementsCount(currentList);
    }
    return (float)valuesCount / hashTable->size;
}

void addValue(HashTable* hashTable, const char* value)
{
    if (getFillFactor(hashTable) > 1)
    {
        resizeHashTable(hashTable, 5);
    }

    const int segmentIndex = hash(value) % hashTable->size;
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

void deleteHashTable(HashTable* hashTable)
{
    for (int i = 0; i < hashTable->size; i++)
    {
        deleteList(hashTable->segments[i]);
    }
    free(hashTable);
}

void resizeHashTable(HashTable* hashTable, const int scale)
{
    HashTable* newHashTable = createHashTable(hashTable->size * scale);
    
    for (int i = 0; i < hashTable->size; i++)
    {
        List* currentList = hashTable->segments[i];

        if (currentList == NULL)
        {
            continue;
        }

        Position* position = first(currentList);
        while (!last(position))
        {
            addValue(newHashTable, getValue(position));
            next(position);
        }

        deletePosition(position);
        deleteList(currentList);
    }

    hashTable->segments = newHashTable->segments;
    hashTable->size = newHashTable->size;

    free(newHashTable);
}

List* getListOfValues(HashTable* hashTable)
{
    List* allValues = createList();

    for (int i = 0; i < hashTable->size; i++)
    {
        List* currentList = hashTable->segments[i];

        if (currentList == NULL)
        {
            continue;
        }

        Position* position = first(currentList);
        while (!last(position))
        {
            addToFront(allValues, getValue(position));
            next(position);
        }

        deletePosition(position);
    }

    return allValues;
}