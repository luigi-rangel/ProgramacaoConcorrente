#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "headers/matrix.h"

matrix loadMatrix(char *filePath)
{
    int i, j, nNodes;
    double weight;
    FILE *fptr;
    matrix adjMatrix;

    // abrindo arquivo que contem o tamanho e a representação do grafo
    fptr = fopen(filePath, "r");
    if (fptr == NULL)
    {
        printf("ERRO: nao foi possivel abrir arquivo\n");
    }

    // lendo o tamanho do grafo
    fscanf(fptr, "# %d", &nNodes);

    adjMatrix.size = nNodes;
    adjMatrix.data = malloc(sizeof(double *) * nNodes);

    for (i = 0; i < nNodes; i++)
    {
        adjMatrix.data[i] = malloc(sizeof(double) * nNodes);

        for (j = 0; j < nNodes; j++)
        {
            adjMatrix.data[i][j] = (i == j) ? 0 : DBL_MAX;
        }
    }
    while (fscanf(fptr, "%d %d {'weight': %lf}", &i, &j, &weight) == 3)
    {
        adjMatrix.data[i][j] = weight;
        adjMatrix.data[j][i] = weight;
    }

    fclose(fptr);

    return adjMatrix;
}

void fPrintMatrix(matrix adjMatrix)
{
    int i, j;
    FILE *fptr;

    // Open a file in writing mode
    fptr = fopen("test.out", "w");    

    for (i = 0; i < adjMatrix.size; i++)
    {
        for (j = 0; j < adjMatrix.size; j++)
        {
            if (adjMatrix.data[i][j] == DBL_MAX)
                fprintf(fptr, " inf ");
                //printf("  -   ");
            // else if (adjMatrix.data[i][j] > 10)
            //     fprintf(fptr, " %.1lf ", adjMatrix.data[i][j]);
                //printf(" %.1lf ", adjMatrix.data[i][j]);
            else
                fprintf(fptr, " %.16lf ", adjMatrix.data[i][j]);
                //printf(" %.2lf ", adjMatrix.data[i][j]);
        }
        fprintf(fptr, "\n");
    }
    fprintf(fptr, "\n");
    // Close the file
    fclose(fptr); 
}

void destroyMatrix(matrix adjMatrix)
{
    int i;

    for (i = 0; i < adjMatrix.size; i++)
    {
        free(adjMatrix.data[i]);
    }

    free(adjMatrix.data);
}