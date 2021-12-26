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

// Копирование текущей позиции
Position* copyPosition(Position* position);

// Добавление элемента после элемента с данной позицией; применяется ко всем элементам, кроме первого
void addAfter(Position* position, int value);

// Добавление элемента в самое начало списка (перед текущим верхним элементом)
void addToFront(List* list, int value);

// Позиция первого элемента (самого верхнего)
Position* first(List* list);

// Перемещение позиции к следующему элементу
void next(Position* position);

// Проверка на последний элемент в списке
bool last(Position* position);

// Получение значения элемента
int get(Position* position);

// Удаление элемента списка после данной позиции; применяется ко всем элементам, кроме первого (возвращает true, если удаление произошло, иначе false)
bool deleteElementAfterPosition(Position* position);

// Удаление первого элемента списка (возвращает true, если удаление произошло, иначе false)
bool deleteFirstElement(List* list);

// Возвращает перевёрнутый список
List* createReversedList(List* source);

// Распечатать список
void printList(List* list);