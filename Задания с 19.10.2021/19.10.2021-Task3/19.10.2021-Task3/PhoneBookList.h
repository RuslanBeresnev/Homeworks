#pragma once

#include <stdbool.h>

// ������ � ���������� �����
typedef struct Note
{
    char name[50];
    char phoneNumber[30];
}Note;

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
void addAfter(Position* position, Note data);

// ���������� �������� � ����� ������ ������ (����� ������� ������� ���������)
void addToStart(List* list, Note data);

// ���������� ������� ������� ��������
Position* getFirstElement(List* list);

// ���������� ������� ���������� ��������
Position* getLastElement(List* list);

// ���������� ������� ���������� ��������
Position* next(Position* position);

// �������� �� ��������� ������� � ������
bool isLast(Position* position);

// �������� �������� ������ ����� ������ �������; ����������� �� ���� ���������, ����� ������� (���������� true, ���� �������� ���������, ����� false)
bool deleteElementAfterPosition(Position* position);

// �������� ������� �������� ������ (���������� true, ���� �������� ���������, ����� false)
bool deleteFirstElement(List* list);

// �������� ����������, ������������ � ��������
Note getData(Position* position);

// ����������� ��� �������� ������
void printList(List* list);

// �������� ��������� �� ������� ������ ����� ��� ������
Position* getPositionByIndex(List* list, int index);

// �������� ���������� � �������� ������
void setData(Position* position, Note data);

// �������� �� ������ ������� ������
bool isEmptyData(Position* position);