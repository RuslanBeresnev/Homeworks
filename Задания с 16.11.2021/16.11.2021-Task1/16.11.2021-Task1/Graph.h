#pragma once

#define MAX_NODES_COUNT 200

// Неориентированный граф
typedef struct Graph Graph;

// Вершина графа
typedef struct Node Node;

// Создать граф
Graph* createGraph(void);

// Создать по номеру вершину и добавить в граф
Node* addNode(Graph* graph, int number);

// Удалить вершину и всё её рёбра из графа
void deleteNode(Node* node);

// Установить номер в вершине
void setNumber(Node* node, int number);

// Получить номер вершины
int getNumber(Node* node);

// Удалить граф
void deleteGraph(Graph* graph);

// Получить список соседних вершин к данной
Node** getNearNodes(Node* node, int* length);

// Получить вес ребра
int getEdge(Node* firstNode, Node* secondNode);

// Установить вес ребра
void setEdge(Node* firstNode, Node* secondNode, int weight);

// Получить вершину по её номеру
Node* getNodeByNumber(Graph* graph, int number);