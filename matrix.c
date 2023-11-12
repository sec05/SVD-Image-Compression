#include "matrix.h";
#include <stdio.h>
#include <stdlib.h>
matrix* makeMatrix(int rows, int cols){
    matrix *m = malloc(sizeof(matrix));
    m->rows = rows;
    m->cols = cols;
    m->data = malloc(sizeof(double) * rows);
    for(int i = 0; i < rows; i++){
        m->data[i] = malloc(sizeof(double) * cols);
    }
    return m;
}

matrix* matrixMultiply(matrix* A, matrix* B){
    if(A->cols != B->rows){
        printf("Error: Matrix dimensions do not match\n");
        return NULL;
    }
    matrix *C = makeMatrix(A->rows, B->cols);
    return C;
}