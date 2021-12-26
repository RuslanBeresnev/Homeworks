#pragma once

#include <stdbool.h>

// Вершина двоичного дерева поиска
typedef struct DictionaryNode DictionaryNode;

// Добавить запись в словарь
void addEntryToDictionary(DictionaryNode** dictionary, const int key, const char value[]);

// Получить значение из словаря по ключу
char* getValueFromDictionary(DictionaryNode* dictionary, const int key);

// Удалить запись из словаря
bool removeEntryFromDictionary(DictionaryNode** dictionary, const int key);

// Проверить наличие записи в словаре (по ключу)
bool entryInDictionary(DictionaryNode* dictionary, const int key);

// Удалить словарь
void deleteDictionary(DictionaryNode* dictionary);