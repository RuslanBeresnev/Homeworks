#pragma once

#include "Graph.h"

#include <stdbool.h>

// Государство
typedef struct State State;

// Создать государство
State* createState(Node* capital);

// Удалить государство
void deleteState(State* state);

// Добавить город в государство
void addCity(State* state, Node* city);

// Вывести номер государства и список его городов
void printCities(State* state);

// Проверить город на принадлежность государству
bool cityInState(State* state, Node* city);

// Получить столицу
Node* getCapital(State* state);

// Получить количество городов в государстве
int getCitiesCount(State* state);