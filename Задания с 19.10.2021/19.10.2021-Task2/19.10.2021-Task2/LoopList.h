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

// ���������� ����� �������
Position* copyPosition(Position* position);

// ���������� �������� ����� �������� � ������ ��������
void addAfter(List* list, Position* position);

// ���������� ������� ������� ��������
Position* getFirstElement(List* list);

// ���������� ������� ���������� ��������
Position* getLastElement(List* list);

// ���������� ����� ������� ���������� ��������
void next(Position* position);

// �������� �� ��������� ������� � ����������� ������
bool isLast(List* list, Position* position);

// ��������� ������ ��������
int getNumber(Position* position);

// �������� �������� ������������ ������ ����� ������ �������
void deleteAfter(List* list, Position* position);