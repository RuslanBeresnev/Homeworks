#pragma once

#include "Graph.h"

#include <stdbool.h>

// �����������
typedef struct State State;

// ������� �����������
State* createState(Node* capital);

// ������� �����������
void deleteState(State* state);

// �������� ����� � �����������
void addCity(State* state, Node* city);

// ������� ����� ����������� � ������ ��� �������
void printCities(State* state);

// ��������� ����� �� �������������� �����������
bool cityInState(State* state, Node* city);

// �������� �������
Node* getCapital(State* state);

// �������� ���������� ������� � �����������
int getCitiesCount(State* state);