#pragma once

#include <stdbool.h>

// Структура словаря
typedef struct DictionaryNode DictionaryNode;

// Добавить запись в словарь
void addEntryToDictionary(DictionaryNode** dictionary, const int key, const char value[]);

// Получить значение по ключу
char* getValueFromDictionary(DictionaryNode* dictionary, const int key);

// Удалить запись из словаря
bool removeEntryFromDictionary(DictionaryNode** dictionary, const int key);

// Проверить нахождение ключа в словаре
bool entryInDictionary(DictionaryNode* dictionary, const int key);

// Удалить словарь
void deleteDictionary(DictionaryNode* dictionary);