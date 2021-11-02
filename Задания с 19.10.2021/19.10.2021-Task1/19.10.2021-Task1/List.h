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

// ���������� �������� � ����� ������ ������ (����� ������� ������� ���������)
void addToStart(List* list, int value);

// ���������� �������� ����� �������� � ������ ��������
void addAfter(Position* position, int value);

// ������� ������� �������� (������ ��������)
Position* first(List* list);

// ����������� ������� � ���������� ��������
Position* next(Position* position);

// �������� �� ��������� ������� � ������
bool last(Position* position);

// ��������� �������� ��������
int get(Position* position);