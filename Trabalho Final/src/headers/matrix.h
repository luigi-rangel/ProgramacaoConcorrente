#pragma once

typedef struct
{
    double **data;
    int size;
} matrix;

matrix loadMatrix(char *filePath);

void fPrintMatrix(matrix adjMatrix);

void destroyMatrix(matrix adjMatrix);