#pragma once

#include "List.h"

// ���-�������
typedef struct HashTable HashTable;

// ������� ���-�������
HashTable* createHashTable(const int size);

// ������� ���-�������
void deleteHashTable(HashTable* hashTable);

// �������� ����������� ������������� ���-�������
float getFillFactor(HashTable* hashTable);

// �������� �������� � ���-�������
void addValue(HashTable* hashTable, const char* value);

// ��������� ������ ���-������� � scale ���
void resizeHashTable(HashTable* hashTable, const int scale);

// �������� ������ �� ����� ���������� � ���-�������
List* getListOfValues(HashTable* hashTable);