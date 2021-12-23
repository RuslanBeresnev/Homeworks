#pragma warning (disable: 4996 5045 6011 6387)

#define MATRIX_SIDE 100

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

bool readMatrixFromFile(const char fileName[], int** matrix, int* width, int* height)
{
    FILE* inputFile = fopen(fileName, "r");
    if (inputFile == NULL)
    {
        fclose(inputFile);
        return -1;
    }

    int heightInput = fscanf(inputFile, "%d", height);
    if (heightInput != 1)
    {
        fclose(inputFile);
        return false;
    }

    int widthInput = fscanf(inputFile, "%d", width);
    if (widthInput != 1)
    {
        fclose(inputFile);
        return false;
    }

    for (int row = 0; row < *height; row++)
    {
        for (int column = 0; column < *width; column++)
        {
            int numberInput = fscanf(inputFile, "%d", &matrix[row][column]);
            if (numberInput != 1)
            {
                fclose(inputFile);
                return false;
            }
        }
    }

    fclose(inputFile);
    return true;
}

void createDotFile(const char fileName[], const int** matrix, const int width, const int height)
{
    FILE* dotFile = fopen(fileName, "w");

    int** ignoredEdges = calloc(MATRIX_SIDE, sizeof(int*));
    for (int i = 0; i < MATRIX_SIDE; i++)
    {
        ignoredEdges[i] = calloc(MATRIX_SIDE, sizeof(int));
    }

    fprintf(dotFile, "digraph TestGraph {\n");
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            if (ignoredEdges[row][column] == 1)
            {
                continue;
            }

            if (matrix[row][column] == 1)
            {
                if (matrix[column][row] == 1)
                {
                    fprintf(dotFile, "%d -> %d [dir=none];\n", row + 1, column + 1);
                    ignoredEdges[column][row] = 1;
                }
                else
                {
                    fprintf(dotFile, "%d -> %d;\n", row + 1, column + 1);
                }
            }
        }
    }
    fprintf(dotFile, "}");

    for (int i = 0; i < MATRIX_SIDE; i++)
    {
        free(ignoredEdges[i]);
    }
    free(ignoredEdges);

    fclose(dotFile);
}

int main(void)
{
    setlocale(LC_ALL, "Russian");

    int** matrix = calloc(MATRIX_SIDE, sizeof(int*));
    for (int i = 0; i < MATRIX_SIDE; i++)
    {
        matrix[i] = calloc(MATRIX_SIDE, sizeof(int));
    }

    int width = 0;
    int height = 0;
    bool successfulMatrixReading = readMatrixFromFile("Matrix.txt", matrix, &width, &height);
    if (!successfulMatrixReading)
    {
        printf("Матрица задана некорректно ...\n");
        return 1;
    }

    createDotFile("TestGraph.dot", matrix, width, height);
    system("dot TestGraph.dot -Tpng -o TestGraph.png");
    system("TestGraph.png");

    free(matrix);
}