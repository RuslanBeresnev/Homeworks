#pragma once

#include <stdbool.h>

// Элемент стека
typedef struct StackElement StackElement;

// Добавляет элемент в стек и возвращает код ошибки
int push(StackElement** head, int number);

// Удаляет верхний элемент из стека и возвращает его значение
int pop(StackElement** head, bool* correctWorking);

// Возвращает значение верхнего элемента, не удаляя его
int top(StackElement** head, bool* correctWorking);

// Проверка стека на пустоту
bool isEmpty(StackElement* head);

// Удаление стека
void deleteStack(StackElement** head);