#include "DoubleDimensionMatrix.h"

#include <stdlib.h>

typedef struct DDMatrix
{
    int* matrix[200];
    int width;
    int height;
} DDMatrix;

void createMatrix(void)
{
    return calloc(1, sizeof(DDMatrix));
}

int getValue(DDMatrix* matrix, const int posX, const int posY)
{
    return matrix->matrix[posX][posY];
}

void setValue(DDMatrix* matrix, const int value, const int posX, const int posY)
{
    matrix->matrix[posX][posY] = value;
}