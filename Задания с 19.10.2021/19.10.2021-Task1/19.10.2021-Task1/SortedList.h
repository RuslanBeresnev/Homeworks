#pragma once

#include "List.h"

// Добавляет число в список
void addNumberToList(List* list, const int number);

// Удаляет число с индексом index из списка
bool removeNumberFromList(List* list, const int index);

// Печатает список
void printList(List* list);