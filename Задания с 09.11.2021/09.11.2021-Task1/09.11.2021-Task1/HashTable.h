#pragma once

#include "List.h"

// Хэш-таблица
typedef struct HashTable HashTable;

// Создать хэш-таблицу
HashTable* createHashTable(void);

// Удалить хэш-таблицу
void deleteHashTable(HashTable* hashTable);

// Вычислить hash у значения
int hash(char* value);

// Добавить значение в хэш-таблицу
void addValue(HashTable* hashTable, char* value);

// Получить частоту значения
int getValueFrequency(HashTable* hashTable, char* value);

// Получить коэффициент заполненности хэш-таблицы
float getFillFactor(HashTable* hashTable);

// Получить длину максимального сегмента в хэш-таблице
int getMaxSegmentLength(HashTable* hashTable);

// Получить среднюю длину сегмента в хэш-таблице
float getAverageSegmentLength(HashTable* hashTable);

// Получить сегмент по индексу
List* getSegmentByIndex(HashTable* hashTable, const int index);