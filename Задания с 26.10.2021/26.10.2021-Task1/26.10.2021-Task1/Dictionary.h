#pragma once

#include <stdbool.h>

// ������� ��������� ������ ������
typedef struct DictionaryNode DictionaryNode;

// �������� ������ � �������
void addEntryToDictionary(DictionaryNode** dictionary, const int key, const char value[]);

// �������� �������� �� ������� �� �����
char* getValueFromDictionary(DictionaryNode* dictionary, const int key);

// ������� ������ �� �������
bool removeEntryFromDictionary(DictionaryNode** dictionary, const int key);

// ��������� ������� ������ � ������� (�� �����)
bool entryInDictionary(DictionaryNode* dictionary, const int key);

// ������� �������
void deleteDictionary(DictionaryNode* dictionary);