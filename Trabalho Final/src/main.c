#include <stdio.h>

#include "headers/matrix.h"

void floydWarshall(matrix input)
{
    int k, i, j, size;
    double **dist;

    size = input.size;
    dist = input.data;

    for (k = 0; k < size; k++)
    {
        for (i = 0; i < size; i++)
        {
            for (j = 0; j < size; j++)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
                else
                {
                    dist[i][j] = dist[i][j];
                }
            }
        }
    }
}

int main(void)
{
    matrix adjMatrix;
    char testFile[] = "./test.in";

    adjMatrix = loadMatrix(testFile);

    floydWarshall(adjMatrix);

    fPrintMatrix(adjMatrix);

    destroyMatrix(adjMatrix);

    return 0;
}