#pragma once

#include <stdbool.h>

// Запись в телефонной книге
typedef struct Note
{
    char name[50];
    char phoneNumber[30];
}Note;

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

// Добавление элемента после элемента с данной позицией; применяется ко всем элементам, кроме первого
void addAfter(Position* position, Note data);

// Добавление элемента в самое начало списка (перед текущим верхним элементом)
void addToStart(List* list, Note data);

// Возвращает позицию первого элемента
Position* getFirstElement(List* list);

// Возвращает позицию последнего элемента
Position* getLastElement(List* list);

// Возвращает позицию следующего элемента
Position* next(Position* position);

// Проверка на последний элемент в списке
bool isLast(Position* position);

// Удаление элемента списка после данной позиции; применяется ко всем элементам, кроме первого (возвращает true, если удаление произошло, иначе false)
bool deleteElementAfterPosition(Position* position);

// Удаление первого элемента списка (возвращает true, если удаление произошло, иначе false)
bool deleteFirstElement(List* list);

// Получить информацию, содержащуюся в элементе
Note getData(Position* position);

// Распечатать все элементы списка
void printList(List* list);

// Получить указатель на элемент списка через его индекс
Position* getPositionByIndex(List* list, int index);

// Изменить информацию в элементе списка
void setData(Position* position, Note data);

// Проверка на пустой элемент списка
bool isEmptyData(Position* position);