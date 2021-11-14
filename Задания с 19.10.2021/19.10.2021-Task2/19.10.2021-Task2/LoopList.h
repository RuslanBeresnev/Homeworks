#pragma once

#include <stdbool.h>

// Список
typedef struct List List;

// Позиция элемента
typedef struct Position Position;

// Создание циклического списка
List* createLoopList(void);

// Удаление циклического списка
void deleteLoopList(List* list);

// Проверка на одноэлементный список
bool oneElementLoopList(List* list);

// Удаление позиции
void deletePosition(Position* position);

// Возвращает копию позиции
Position* copyPosition(Position* position);

// Добавление элемента после элемента с данной позицией
void addAfter(List* list, Position* position);

// Возврашает позицию первого элемента
Position* getFirstElement(List* list);

// Возвращает позицию последнего элемента
Position* getLastElement(List* list);

// Возвращает копию позиции следующего элемента
void next(Position* position);

// Проверка на последний элемент в циклическом списке
bool isLast(List* list, Position* position);

// Получение номера элемента
int getNumber(Position* position);

// Удаление элемента циклического списка после данной позиции
void deleteAfter(List* list, Position* position);