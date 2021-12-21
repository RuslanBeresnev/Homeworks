#pragma once

#include <stdbool.h>

// Очередь с приоритетом
typedef struct PriorityQueue PriorityQueue;

// Создать очередь с приоритетом
PriorityQueue* createPriorityQueue(void);

// Удалить очередь с приоритетом
void deletePriorityQueue(PriorityQueue* queue);

// Добавление элемента
void enqueue(PriorityQueue* queue, int value, int priority);

// Получить элемент с наивысшим приоритетом
int dequeue(PriorityQueue* queue);

// Проверка на пустоту
bool isEmpty(PriorityQueue* queue);