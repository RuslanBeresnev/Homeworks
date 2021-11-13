#pragma once

#include <stdbool.h>

// ������� �����
typedef struct StackElement StackElement;

// ��������� ������� � ���� � ���������� ��� ������
int push(StackElement** head, int number);

// ������� ������� ������� �� ����� � ���������� ��� ��������
int pop(StackElement** head, bool* correctWorking);

// �������� ����� �� �������
bool isEmpty(StackElement* head);

// �������� �����
void deleteStack(StackElement** head);