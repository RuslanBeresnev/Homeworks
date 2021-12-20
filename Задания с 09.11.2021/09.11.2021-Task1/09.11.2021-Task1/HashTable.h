#pragma once

// Хэш-таблица
typedef struct HashTable HashTable;

// Создать хэш-таблицу
HashTable* createHashTable(const int size);

// Удалить хэш-таблицу
void deleteHashTable(HashTable* hashTable);

// Добавить значение в хэш-таблицу
void addValue(HashTable* hashTable, const char* value);

// Получить коэффициент заполненности хэш-таблицы
float getFillFactor(HashTable* hashTable);

// Получить длину максимального сегмента в хэш-таблице
int getMaxSegmentLength(HashTable* hashTable);

// Получить среднюю длину сегмента в хэш-таблице
float getAverageSegmentLength(HashTable* hashTable);

// Напечатать частоты всех слов
void printWordsFrequences(HashTable* hashTable);

// Увеличить размер хэш-таблицы в scale раз
void resizeHashTable(HashTable* hashTable, const int scale);

// Получить размер хэш-таблицы
int getSegmentsCount(HashTable* hashTable);