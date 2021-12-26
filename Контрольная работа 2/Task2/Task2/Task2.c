#pragma warning (disable: 4996 6387)

#define MATRIX_SIDE 30

#include <stdio.h>
#include <locale.h>

// Создаёт транзитивное замыкание отношения
void createTransitiveClosure(int matrix[MATRIX_SIDE][MATRIX_SIDE], const int side)
{
    for (int k = 0; k < side; k++)
    {
        for (int i = 0; i < side; i++)
        {
            for (int j = 0; j < side; j++)
            {
                matrix[i][j] = matrix[i][j] || (matrix[i][k] && matrix[k][j]);
            }
        }
    }
}

// Считывает матрицу из файла и возвращает длину её стороны
int readMatrixFromFile(const char fileName[], int matrix[MATRIX_SIDE][MATRIX_SIDE])
{
    FILE* inputFile = fopen(fileName, "r");
    if (inputFile == NULL)
    {
        fclose(inputFile);
        return -1;
    }
    int linesRead = 0;
    int count = 0;
    while (!feof(inputFile))
    {
        if (linesRead == 0)
        {
            int countInput = fscanf(inputFile, "%d", &count);
            if (countInput != 1)
            {
                fclose(inputFile);
                return linesRead;
            }
        }
        for (int j = 0; j < count; j++)
        {
            int numberInput = fscanf(inputFile, "%d", &matrix[linesRead][j]);
            if (numberInput != 1)
            {
                fclose(inputFile);
                return linesRead;
            }
        }
        linesRead++;
    }
    fclose(inputFile);
    return count;
}

// Печатает матрицу в файл
int printMatrixToFile(const char fileName[], const int matrix[MATRIX_SIDE][MATRIX_SIDE], const int side)
{
    FILE* outputFile = fopen(fileName, "w");
    if (outputFile == NULL)
    {
        fclose(outputFile);
        return 1;
    }
    for (int i = 0; i < side; i++)
    {
        for (int j = 0; j < side; j++)
        {
            fprintf(outputFile, "%d ", matrix[i][j]);
        }
        fprintf(outputFile, "\n");
    }
    fclose(outputFile);
    return 0;
}

int main(void)
{
    setlocale(LC_ALL, "Russian");
    int matrix[MATRIX_SIDE][MATRIX_SIDE];
    const int side = readMatrixFromFile("input.txt", matrix);
    if (side < 1)
    {
        printf("В файле содержатся некорректные данные или файл пуст ...\n");
        return 1;
    }

    createTransitiveClosure(matrix, side);
    const int errorCode = printMatrixToFile("output.txt", matrix, side);
    if (errorCode != 0)
    {
        printf("Что-то пошло не так, и матрица не была распечатана ...\n");
        return 1;
    }
    printf("Матрица транзитивного замыкания успешно напечатана в выходной файл\n");
}