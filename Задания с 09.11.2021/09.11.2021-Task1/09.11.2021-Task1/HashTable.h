#pragma once

#include "List.h"

// ���-�������
typedef struct HashTable HashTable;

// ������� ���-�������
HashTable* createHashTable(void);

// ������� ���-�������
void deleteHashTable(HashTable* hashTable);

// ��������� hash � ��������
int hash(char* value);

// �������� �������� � ���-�������
void addValue(HashTable* hashTable, char* value);

// �������� ������� ��������
int getValueFrequency(HashTable* hashTable, char* value);

// �������� ����������� ������������� ���-�������
float getFillFactor(HashTable* hashTable);

// �������� ����� ������������� �������� � ���-�������
int getMaxSegmentLength(HashTable* hashTable);

// �������� ������� ����� �������� � ���-�������
float getAverageSegmentLength(HashTable* hashTable);

// �������� ������� �� �������
List* getSegmentByIndex(HashTable* hashTable, const int index);