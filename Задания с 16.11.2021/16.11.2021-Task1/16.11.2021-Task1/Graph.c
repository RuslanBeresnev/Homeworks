#pragma warning (disable: 4820 5045 6011)

#include "Graph.h"
#include <stdlib.h>

typedef struct Node
{
    int number;
    Graph* graph;
} Node;

typedef struct Graph
{
    Node* nodes[MAX_NODES_COUNT];
    int nodesCount;
    int matrix[MAX_NODES_COUNT][MAX_NODES_COUNT];
} Graph;

Graph* createGraph(void)
{
    return calloc(1, sizeof(Graph));
}

int getEdge(Node* firstNode, Node* secondNode)
{
    return firstNode->graph->matrix[firstNode->number][secondNode->number];
}

void setEdge(Node* firstNode, Node* secondNode, int weight)
{
    firstNode->graph->matrix[firstNode->number][secondNode->number] = weight;
    secondNode->graph->matrix[secondNode->number][firstNode->number] = weight;
}

Node* addNode(Graph* graph, int number)
{
    if (graph->nodes[number] != NULL)
    {
        return graph->nodes[number];
    }

    Node* newNode = calloc(1, sizeof(Node));
    newNode->graph = graph;
    newNode->number = number;

    graph->nodes[number] = newNode;
    graph->nodesCount++;

    return newNode;
}

void deleteNode(Node* node)
{
    node->graph->nodes[node->number] = NULL;
    node->graph->nodesCount--;

    for (int i = 0; i < MAX_NODES_COUNT; i++)
    {
        node->graph->matrix[node->number][i] = 0;
        node->graph->matrix[i][node->number] = 0;
    }

    free(node);
}

void setNumber(Node* node, int number)
{
    node->number = number;
}

int getNumber(Node* node)
{
    return node->number;
}

void deleteGraph(Graph* graph)
{
    for (int i = 0; i < MAX_NODES_COUNT; i++)
    {
        if (graph->nodes[i] != NULL)
        {
            free(graph->nodes[i]);
        }
    }
    free(graph);
}

Node** getNearNodes(Node* node, int* count)
{
    Node** nearNodes = calloc(200, sizeof(Node*));
    int realCount = 0;
    for (int i = 0; i < MAX_NODES_COUNT; i++)
    {
        if (node->graph->matrix[node->number][i] != 0)
        {
            nearNodes[realCount] = node->graph->nodes[i];
            (*count)++;
            realCount++;
        }
    }
    return nearNodes;
}

Node* getNodeByNumber(Graph* graph, int number)
{
    return graph->nodes[number];
}