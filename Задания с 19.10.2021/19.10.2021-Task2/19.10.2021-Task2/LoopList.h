#pragma once

#include <stdbool.h>

// ������
typedef struct List List;

// ������� ��������
typedef struct Position Position;

// �������� ������������ ������
List* createLoopList(void);

// �������� ������������ ������
void deleteLoopList(List* list);

// �������� �� �������������� ������
bool oneElementLoopList(List* list);

// �������� �������
void deletePosition(Position* position);

// ���������� �������� ����� �������� � ������ ��������
void addAfter(Position* position);

// ���������� ������� ������� ��������
Position* getFirstElement(List* list);

// ���������� ������� ���������� ��������
Position* getLastElement(List* list);

// ���������� ����� ������� ���������� ��������
Position* next(Position* position);

// �������� �� ��������� ������� � ����������� ������
bool isLast(List* list, Position* position);

// ��������� ������ ��������
int getNumber(Position* position);

// �������� �������� ������������ ������ ����� ������ �������
void deleteAfter(List* list, Position* position);