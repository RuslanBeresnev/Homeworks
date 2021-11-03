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

// ���������� �������� ����� �������� � ������ ��������; ����������� �� ���� ���������, ����� �������
void addAfter(Position* position, int value);

// ���������� �������� � ����� ������ ������ (����� ������� ������� ���������)
void addToStart(List* list, int value);

// ������� ������� �������� (������ ��������)
Position* first(List* list);

// ����������� ������� � ���������� ��������
Position* next(Position* position);

// �������� �� ��������� ������� � ������
bool last(Position* position);

// ��������� �������� ��������
int get(Position* position);

// �������� �������� ������ ����� ������ �������; ����������� �� ���� ���������, ����� ������� (���������� true, ���� �������� ���������, ����� false)
bool deleteElementAfterPosition(Position* position);

// �������� ������� �������� ������ (���������� true, ���� �������� ���������, ����� false)
bool deleteFirstElement(List* list);