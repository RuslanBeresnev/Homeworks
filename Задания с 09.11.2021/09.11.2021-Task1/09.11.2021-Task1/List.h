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
void addAfter(Position* position, char* value);

// Добавление элемента в самое начало списка (перед текущим верхним элементом)
void addToFront(List* list, char* value);

// Позиция первого элемента (самого верхнего)
Position* first(List* list);

// Перемещение позиции к следующему элементу
void next(Position* position);

// Проверка на последний элемент в списке
bool last(Position* position);

// Получение значения элемента
char* getValue(Position* position);

// Получение частоты значения
int getElementFrequency(Position* position);

// Удаление элемента списка после данной позиции; применяется ко всем элементам, кроме первого (возвращает true, если удаление произошло, иначе false)
bool deleteElementAfterPosition(Position* position);

// Удаление первого элемента списка (возвращает true, если удаление произошло, иначе false)
bool deleteFirstElement(List* list);

// Проверка на содержание элемента в списке
bool valueInList(List* list, char* value);

// Изменить частоту появления элемента
void setFrequency(Position* position, const int frequency);

// Получить позицию по значению элемента
Position* getPositionByValue(List* list, char* value);

// Получить длину списка
int getLength(List* list);