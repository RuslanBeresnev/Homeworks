#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>

void createDotFile(const char fileName[], const int matrix[][5], const int width, const int height)
{
    FILE* dotFile = fopen(fileName, "w");

    int ignoredEdges[25][2];
    for (int i = 0; i < 25; i++)
    {
        ignoredEdges[i][0] = 0;
        ignoredEdges[i][1] = 0;
    }

    fprintf(dotFile, "digraph TestGraph {\n");
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (ignoredEdges[y][x] == 1)
            {
                continue;
            }

            if (matrix[y][x] == 1)
            {
                if (matrix[x][y] == 1)
                {
                    fprintf(dotFile, "%d -> %d [dir=none];\n", y + 1, x + 1);
                    ignoredEdges[x][y] = 1;
                }
                else
                {
                    fprintf(dotFile, "%d -> %d;\n", y + 1, x + 1);
                }
            }
        }
    }
    fprintf(dotFile, "}");

    fclose(dotFile);
}

int main(void)
{
    const int matrix[5][5] = { 
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1}, 
        {0, 0, 0, 0, 0},
        {1, 1, 0, 0, 1} };

    createDotFile("TestGraph.dot", matrix, 5, 5);
    system("dot TestGraph.dot -Tpng -o TestGraph.png");
    system("TestGraph.png");
}