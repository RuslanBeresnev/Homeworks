#pragma once

#include "List.h"

// ��������� ����� � ������
void addNumberToList(List* list, const int number);

// ������� ����� � �������� index �� ������
bool removeNumberFromList(List* list, const int index);

// �������� ������
void printList(List* list);