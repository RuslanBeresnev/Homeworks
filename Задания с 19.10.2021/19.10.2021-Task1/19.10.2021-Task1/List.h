#pragma once

#include <stdbool.h>

// Список
typedef struct List List;

// Позиция элемента
typedef struct Position Position;

// Создание списка
List* createList(void);

// Удаление списка
void deleteList(List* list);

// Удаление позиции
void deletePosition(Position* position);

// Добавление элемента в самое начало списка (перед текущим верхним элементом)
void addToStart(List* list, int value);

// Добавление элемента после элемента с данной позицией
void addAfter(Position* position, int value);

// Позиция первого элемента (самого верхнего)
Position* first(List* list);

// Перемещение позиции к следующему элементу
Position* next(Position* position);

// Проверка на последний элемент в списке
bool last(Position* position);

// Получение значения элемента
int get(Position* position);