#pragma once

#include <stdbool.h>

// Структура словаря
typedef struct DictionaryNode DictionaryNode;

// Добавить запись в словарь
DictionaryNode* addEntryToDictionary(DictionaryNode* dictionary, const char* key, const char* value);

// Получить значение по ключу
char* getValueFromDictionary(DictionaryNode* dictionary, const char* key);

// Удалить запись из словаря
DictionaryNode* removeEntryFromDictionary(DictionaryNode* dictionary, const char* key, bool* entryRemoved);

// Проверить нахождение ключа в словаре
bool entryInDictionary(DictionaryNode* dictionary, const char* key);

// Удалить словарь
void deleteDictionary(DictionaryNode* dictionary);

// Малый левый поворот
DictionaryNode* rotateLeft(DictionaryNode* a);

// Малый правый поворот
DictionaryNode* rotateRight(DictionaryNode* a);

// Большой левый поворот
DictionaryNode* bigRotateLeft(DictionaryNode* a);

// Большой правый поворот
DictionaryNode* bigRotateRight(DictionaryNode* a);

// Получить высоту дерева
int getHeight(DictionaryNode* dictionary);

// Пересчитать высоту дерева
int calculateHeight(DictionaryNode* dictionary);

// Посчитать разницу между высотой правого поддерева и высотой левого поддерева
int calculateDifference(DictionaryNode* dictionary);

// Пересчитать и исправить значения параметра высоты в каждой вершине
void correctHeightsInTree(DictionaryNode* dictionary);

// Балансировка дерева
DictionaryNode* balance(DictionaryNode* dictionary);