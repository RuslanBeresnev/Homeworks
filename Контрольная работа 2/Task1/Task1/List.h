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
void addAfter(Position* position, int value);

// ���������� �������� � ����� ������ ������ (����� ������� ������� ���������)
void addToFront(List* list, int value);

// ������� ������� �������� (������ ��������)
Position* first(List* list);

// ����������� ������� � ���������� ��������
void next(Position* position);

// �������� �� ��������� ������� � ������
bool last(Position* position);

// ��������� �������� ��������
int get(Position* position);

// �������� �������� ������ ����� ������ �������; ����������� �� ���� ���������, ����� ������� (���������� true, ���� �������� ���������, ����� false)
bool deleteElementAfterPosition(Position* position);

// �������� ������� �������� ������ (���������� true, ���� �������� ���������, ����� false)
bool deleteFirstElement(List* list);

// ���������� ����������� ������
List* createReversedList(List* source);

// ����������� ������
void printList(List* list);