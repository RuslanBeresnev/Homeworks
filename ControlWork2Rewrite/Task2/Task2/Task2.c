#pragma warning (disable: 4996 6387)

#define MATRIX_SIDE 30

#include <stdio.h>
#include <locale.h>

// Надо было использовать списки ...
void createAdjacencyArrayByIncidenceMatrix(const int incidenceMatrix[][1], const int width, const int height,
    int AdjacencyArray[][MATRIX_SIDE])
{
    for (int i = 0; i < height; i++)
    {
        int adjacencyNodesCount = 0;
        for (int j = 0; j < width; j++)
        {
            if (incidenceMatrix[i][j] == 1)
            {
                for (int k = 0; k < height; k++)
                {
                    if (incidenceMatrix[k][j] == 1 && k != i)
                    {
                        AdjacencyArray[i][adjacencyNodesCount] = k;
                        adjacencyNodesCount++;
                        break;
                    }
                }
            }
        }
    }
}

int main(void)
{
    setlocale(LC_ALL, "Russian");
    int incidenceMatrix[3][1] = {{1},
                                 {1},
                                 {0}};

    int adjacencyArray[MATRIX_SIDE][MATRIX_SIDE];
    createAdjacencyArrayByIncidenceMatrix(incidenceMatrix, 1, 3, adjacencyArray);
}

// :(