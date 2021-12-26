#pragma once

// ���-�������
typedef struct HashTable HashTable;

// ������� ���-�������
HashTable* createHashTable(const int size);

// ������� ���-�������
void deleteHashTable(HashTable* hashTable);

// �������� �������� � ���-�������
void addValue(HashTable* hashTable, const char* value);

// �������� ����������� ������������� ���-�������
float getFillFactor(HashTable* hashTable);

// �������� ����� ������������� �������� � ���-�������
int getMaxSegmentLength(HashTable* hashTable);

// �������� ������� ����� �������� � ���-�������
float getAverageSegmentLength(HashTable* hashTable);

// ���������� ������� ���� ����
void printWordsFrequences(HashTable* hashTable);

// ��������� ������ ���-������� � scale ���
void resizeHashTable(HashTable* hashTable, const int scale);

// �������� ������ ���-�������
int getSegmentsCount(HashTable* hashTable);