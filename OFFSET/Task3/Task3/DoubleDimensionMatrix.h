#pragma once

typedef struct DDMatrix DDMatrix;

// Создание двухмерной матрицы
void createMatrix(void);

// Удаление матрицы
void deleteMatrix(DDMatrix* matrix);

// Получить значение
int getValue(DDMatrix* matrix, const int posX, const int posY);

// Установить значение
void setValue(DDMatrix* matrix, const int value, const int posX, const int posY);

// Ввести матрицу из файла
void inputFromFile(DDMatrix* matrix, const char fileName[]);

// Напечатать матрицу
void printMatrix(DDMatrix* matrix);

// Получить все седловые точки матрицы
void getSaddlePoints(DDMatrix* matrix, int points[]);