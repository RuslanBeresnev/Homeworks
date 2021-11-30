#pragma once

#include <stdbool.h>

// ������
typedef struct List List;

// ������� ��������
typedef struct Position Position;

// �������� ������
List* createList(void);

// �������� ������
void deleteList(List* list);

// �������� �������
void deletePosition(Position* position);

// ����������� ������� �������
Position* copyPosition(Position* position);

// ���������� �������� ����� �������� � ������ ��������; ����������� �� ���� ���������, ����� �������
void addAfter(Position* position, char* value);

// ���������� �������� � ����� ������ ������ (����� ������� ������� ���������)
void addToFront(List* list, char* value);

// ������� ������� �������� (������ ��������)
Position* first(List* list);

// ����������� ������� � ���������� ��������
void next(Position* position);

// �������� �� ��������� ������� � ������
bool last(Position* position);

// ��������� �������� ��������
char* getValue(Position* position);

// ��������� ������� ��������
int getElementFrequency(Position* position);

// �������� �������� ������ ����� ������ �������; ����������� �� ���� ���������, ����� ������� (���������� true, ���� �������� ���������, ����� false)
bool deleteElementAfterPosition(Position* position);

// �������� ������� �������� ������ (���������� true, ���� �������� ���������, ����� false)
bool deleteFirstElement(List* list);

// �������� �� ���������� �������� � ������
bool valueInList(List* list, char* value);

// �������� ������� ��������� ��������
void setFrequency(Position* position, const int frequency);

// �������� ������� �� �������� ��������
Position* getPositionByValue(List* list, char* value);

// �������� ����� ������
int getLength(List* list);