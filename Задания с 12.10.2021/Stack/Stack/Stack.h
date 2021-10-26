#pragma once

#include <stdbool.h>

// ������� �����
typedef struct StackElement StackElement;

// ��������� ������� � ����
void push(StackElement** head, float number);

// ������� ������� ������� �� �����
float pop(StackElement** head);

// �������� ����� �� �������
bool isEmpty(StackElement* head);

// �������� �����
void deleteStack(StackElement** head);