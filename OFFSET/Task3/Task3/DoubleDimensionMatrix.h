#pragma once

typedef struct DDMatrix DDMatrix;

// �������� ���������� �������
void createMatrix(void);

// �������� �������
void deleteMatrix(DDMatrix* matrix);

// �������� ��������
int getValue(DDMatrix* matrix, const int posX, const int posY);

// ���������� ��������
void setValue(DDMatrix* matrix, const int value, const int posX, const int posY);

// ������ ������� �� �����
void inputFromFile(DDMatrix* matrix, const char fileName[]);

// ���������� �������
void printMatrix(DDMatrix* matrix);

// �������� ��� �������� ����� �������
void getSaddlePoints(DDMatrix* matrix, int points[]);