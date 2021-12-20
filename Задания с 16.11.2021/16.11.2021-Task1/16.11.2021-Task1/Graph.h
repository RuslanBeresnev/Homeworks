#pragma once

#define MAX_NODES_COUNT 200

// ����������������� ����
typedef struct Graph Graph;

// ������� �����
typedef struct Node Node;

// ������� ����
Graph* createGraph(void);

// ������� �� ������ ������� � �������� � ����
Node* addNode(Graph* graph, int number);

// ������� ������� � �� � ���� �� �����
void deleteNode(Node* node);

// ���������� ����� � �������
void setNumber(Node* node, int number);

// �������� ����� �������
int getNumber(Node* node);

// ������� ����
void deleteGraph(Graph* graph);

// �������� ������ �������� ������ � ������
Node** getNearNodes(Node* node, int* length);

// �������� ��� �����
int getEdge(Node* firstNode, Node* secondNode);

// ���������� ��� �����
void setEdge(Node* firstNode, Node* secondNode, int weight);

// �������� ������� �� � ������
Node* getNodeByNumber(Graph* graph, int number);