#pragma once

#include "List.h"

// Хэш-таблица
typedef struct HashTable HashTable;

// Создать хэш-таблицу
HashTable* createHashTable(const int size);

// Удалить хэш-таблицу
void deleteHashTable(HashTable* hashTable);

// Получить коэффициент заполненности хэш-таблицы
float getFillFactor(HashTable* hashTable);

// Добавить значение в хэш-таблицу
void addValue(HashTable* hashTable, const char* value);

// Увеличить размер хэш-таблицы в scale раз
void resizeHashTable(HashTable* hashTable, const int scale);

// Получить список со всеми значениями в хэш-таблице
List* getListOfValues(HashTable* hashTable);