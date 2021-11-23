#include <stdio.h>

// Создаёт транзитивное замыкание отношения
void createTransitiveClosure(const int sourceMatrix[100][100], int destinationMatrix[100][100], const int sourceHeight, const int sourceWidth)
{
    for (int i = 0; i < sourceHeight; i++)
    {
        for (int j = 0; j < sourceWidth; j++)
        {
            for (int k = 0; k < sourceWidth; k++)
            {
                if (sourceMatrix[i][j] == 1 && sourceMatrix[j][k] == 1)
                {
                    destinationMatrix[i][k] = 1;
                }
            }
        }
    }
}

// Считывает матрицу из файла и возвращает длину её стороны
int readMatrixFromFile(const char fileName[], int matrix[100][100])
{
    // pass
}

// Печатает матрицу в файл
void printMatrixToFile(const char fileName[], int matrix[100][100])
{
    // pass
}

int main(void)
{
    int sourceMatrix[30][30];
    int size = readMatrixFromFile("input.txt", sourceMatrix);

    int transitiveClosureMatrix[30][30];
    createTransitiveClosure(sourceMatrix, transitiveClosureMatrix, size, size);
    printMatrixToFile("output.txt", transitiveClosureMatrix);
}