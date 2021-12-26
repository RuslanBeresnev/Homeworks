#pragma once

#include <stdbool.h>

// ������� � �����������
typedef struct PriorityQueue PriorityQueue;

// ������� ������� � �����������
PriorityQueue* createPriorityQueue(void);

// ������� ������� � �����������
void deletePriorityQueue(PriorityQueue* queue);

// ���������� ��������
void enqueue(PriorityQueue* queue, int value, int priority);

// �������� ������� � ��������� �����������
int dequeue(PriorityQueue* queue);

// �������� �� �������
bool isEmpty(PriorityQueue* queue);