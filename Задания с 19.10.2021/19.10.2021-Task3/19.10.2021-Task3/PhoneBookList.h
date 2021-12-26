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
void addAfter(List* list, Position* position, Note data);

// ���������� �������� � ����� ������ ������ (����� ������� ������� ���������)
void addToHead(List* list, Note data);

// ���������� ������� ������� ��������
Position* getFirstElement(List* list);

// ���������� ������� ���������� ��������
Position* getLastElement(List* list);

// ���������� ������� ���������� ��������
void next(Position* position);

// �������� �� ��������� ������� � ������
bool isLast(Position* position);

// �������� �������� ������ ����� ������ �������; ����������� �� ���� ���������, ����� ������� (���������� true, ���� �������� ���������, ����� false)
bool deleteElementAfterPosition(List* list, Position* position);

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

// ���������� ����� ������
int getLength(List* list);

// ���������� ��� ������ (���������� true, ���� ��� �����, ����� false)
bool listsAreEqual(List* firstList, List* secondList);