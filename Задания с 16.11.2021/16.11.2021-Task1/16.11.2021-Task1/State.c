#pragma warning (disable: 4820 5045 6011)

#include "State.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct State
{
    Node* cities[200];
    Node* capital;
    int citiesCount;
} State;

void addCity(State* state, Node* city)
{
    state->cities[getNumber(city)] = city;
    state->citiesCount++;
}

State* createState(Node* capital)
{
    State* newState = calloc(1, sizeof(State));
    addCity(newState, capital);
    newState->capital = capital;
    newState->citiesCount = 1;
    return newState;
}

void deleteState(State* state)
{
    free(state);
}

void printCities(State* state)
{
    printf("√осударство с номером %d содержит города: ", getNumber(state->capital));
    for (int i = 0; i < MAX_NODES_COUNT; i++)
    {
        if (state->cities[i] != NULL)
        {
            printf("%d ", i);
        }
    }
    printf("\n");
}

bool cityInState(State* state, Node* city)
{
    if (city == NULL)
    {
        return false;
    }

    for (int i = 0; i < 200; i++)
    {
        if (state->cities[i] == city)
        {
            return true;
        }
    }
    return false;
}

Node* getCapital(State* state)
{
    return state->capital;
}

int getCitiesCount(State* state)
{
    return state->citiesCount;
}