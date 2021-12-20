#pragma warning (disable: 4996 5045)

#include "State.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int buildGraphAndCreateStatesFromFile(const char fileName[], Graph* cities, State* states[])
{
    FILE* inputFile = fopen(fileName, "r");
    if (inputFile == NULL)
    {
        return -1;
    }
    int linesRead = 0;

    int citiesCount = 0;
    int roadsCount = 0;
    int statesCount = 0;

    while (!feof(inputFile))
    {
        if (linesRead == 0)
        {
            int citiesCountInput = fscanf(inputFile, "%d", &citiesCount);
            if (citiesCountInput != 1)
            {
                fclose(inputFile);
                return -1;
            }
            int roadsCountInput = fscanf(inputFile, "%d", &roadsCount);
            if (roadsCountInput != 1)
            {
                fclose(inputFile);
                return -1;
            }
            linesRead++;
            continue;
        }

        for (int i = 0; i < roadsCount; i++)
        {
            int firstCityNumber = 0;
            int secondCityNumber = 0;
            int roadLength = 0;

            int firstCityInput = fscanf(inputFile, "%d", &firstCityNumber);
            if (firstCityInput != 1)
            {
                fclose(inputFile);
                return -1;
            }

            int secondCityInput = fscanf(inputFile, "%d", &secondCityNumber);
            if (secondCityInput != 1)
            {
                fclose(inputFile);
                return -1;
            }

            int roadLengthInput = fscanf(inputFile, "%d", &roadLength);
            if (roadLengthInput != 1)
            {
                fclose(inputFile);
                return -1;
            }

            Node* firstCity = addNode(cities, firstCityNumber);
            Node* secondCity = addNode(cities, secondCityNumber);
            setEdge(firstCity, secondCity, roadLength);

            linesRead++;
        }

        int statesCountInput = fscanf(inputFile, "%d", &statesCount);
        if (statesCountInput != 1)
        {
            fclose(inputFile);
            return -1;
        }
        for (int i = 0; i < statesCount; i++)
        {
            int capitalNumber = 0;
            int capitalNumberInput = fscanf(inputFile, "%d", &capitalNumber);
            if (capitalNumberInput != 1)
            {
                fclose(inputFile);
                return linesRead - 2 - roadsCount;
            }

            State* newState = createState(getNodeByNumber(cities, capitalNumber));
            states[i] = newState;

            linesRead++;
        }
    }
    fclose(inputFile);
    return statesCount;
}

bool cityIsTerraNullius(Node* city, State* states[], const int statesCount)
{
    for (int i = 0; i < statesCount; i++)
    {
        if (cityInState(states[i], city))
        {
            return false;
        }
    }
    return true;
}

bool allCitiesDistributed(Graph* cities, State* states[], const int statesCount)
{
    for (int i = 0; i < MAX_NODES_COUNT; i++)
    {
        Node* currentCity = getNodeByNumber(cities, i);
        if (currentCity != NULL && cityIsTerraNullius(currentCity, states, statesCount))
        {
            return false;
        }
    }
    return true;
}

bool nodeIsVisited(Node* node, Node* visitedNodes[], int count)
{
    for (int i = 0; i < count; i++)
    {
        if (node == visitedNodes[i])
        {
            return true;
        }
    }
    return false;
}

void visitNode(State* currentState, Node* startCity, Node* deepSpanningTree[], int* deepSpanningTreeLength, int* minimumDistance,
    Node** nearestCity, State* states[], const int statesCount)
{
    deepSpanningTree[*deepSpanningTreeLength] = startCity;
    (*deepSpanningTreeLength)++;

    int nearNodesCount = 0;
    Node** nearNodes = getNearNodes(startCity, &nearNodesCount);

    for (int i = 0; i < nearNodesCount; i++)
    {
        if (!nodeIsVisited(nearNodes[i], deepSpanningTree, *deepSpanningTreeLength))
        {
            if (cityIsTerraNullius(nearNodes[i], states, statesCount) && getEdge(startCity, nearNodes[i]) < *minimumDistance)
            {
                *minimumDistance = getEdge(startCity, nearNodes[i]);
                *nearestCity = nearNodes[i];
                continue;
            }
            if (cityInState(currentState, nearNodes[i]))
            {
                visitNode(currentState, nearNodes[i], deepSpanningTree, deepSpanningTreeLength, minimumDistance, nearestCity, states, statesCount);
            }
        }
    }

    free(nearNodes);
}

Node* getNearestUnoccupiedCity(State* state, Node* startCity, State* states[], const int statesCount)
{
    Node** deepSpanningTree = calloc(getCitiesCount(state), sizeof(Node*));
    int deepSpanningTreeLength = 0;

    int minimumDistance = 1000000;
    Node* nearestCity = NULL;

    visitNode(state, startCity, deepSpanningTree, &deepSpanningTreeLength, &minimumDistance, &nearestCity, states, statesCount);
    free(deepSpanningTree);

    return nearestCity;
}

void distributeCitiesAmongStates(Graph* cities, State* states[], int statesCount)
{
    int stateIndex = 0;
    while (!allCitiesDistributed(cities, states, statesCount))
    {
        State* currentState = states[stateIndex % statesCount];
        Node* nearestUnoccupiedCity = getNearestUnoccupiedCity(currentState, getCapital(currentState), states, statesCount);
        if (nearestUnoccupiedCity == NULL)
        {
            stateIndex++;
            continue;
        }
        addCity(currentState, nearestUnoccupiedCity);
        stateIndex++;
    }
}

bool generalTestPassed(void)
{
    Graph* cities = createGraph();
    State* states[10] = { NULL };

    const int statesCount = buildGraphAndCreateStatesFromFile("Test Input.txt", cities, states);
    if (statesCount == -1)
    {
        return false;
    }
    distributeCitiesAmongStates(cities, states, statesCount);

    bool verdict = false;
    Node* firstCity = getNodeByNumber(cities, 1);
    Node* secondCity = getNodeByNumber(cities, 2);
    Node* thirdCity = getNodeByNumber(cities, 3);
    Node* fourthCity = getNodeByNumber(cities, 4);
    Node* fifthCity = getNodeByNumber(cities, 5);

    if (cityInState(states[0], firstCity) && cityInState(states[0], thirdCity) && cityInState(states[0], fifthCity) && cityInState(states[1], secondCity)
        && cityInState(states[1], fourthCity))
    {
        verdict = true;
    }

    for (int i = 0; i < statesCount; i++)
    {
        deleteState(states[i]);
    }
    deleteGraph(cities);

    return verdict;
}

int main(void)
{
    if (!generalTestPassed())
    {
        printf("Tests Failed ...\n");
        return 1;
    }

    setlocale(LC_ALL, "Russian");

    Graph* cities = createGraph();
    State* states[50] = { NULL };

    const int statesCount = buildGraphAndCreateStatesFromFile("Input.txt", cities, states);
    if (statesCount == -1)
    {
        printf("Что-то пошло не так ...\n");
        return 1;
    }
    distributeCitiesAmongStates(cities, states, statesCount);

    for (int i = 0; i < statesCount; i++)
    {
        printCities(states[i]);
        deleteState(states[i]);
    }

    deleteGraph(cities);
}