#pragma once

#include <stdbool.h>

// Элемент стека
typedef struct StackElement StackElement;

// Добавляет элемент в стек
void push(StackElement** head, int number);

// Удаляет верхний элемент из стека
int pop(StackElement** head);

// Проверка стека на пустоту
bool isEmpty(StackElement* head);

// Удаление стека
void deleteStack(StackElement** head);