#include "matrixAlgorithims.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

matrix** reducedQR(matrix *A){
    return modifiedGrahamSchmidt(A);
}

matrix** fullQR(matrix *A){
    matrix** rQR = reducedQR(A);
    matrix* Q = makeMatrix(A->rows, A->rows);
    matrix* R = makeMatrix(A->rows, A->cols);
    for(int i = 0; i < A->rows; i++){
        for(int j = 0; j < A->cols; j++){
            Q->data[i][j] = rQR[0]->data[i][j];
        }
    }
    for(int i = 0; i < A->cols; i++){
        for(int j = 0; j < A->cols; j++){
            R->data[i][j] = rQR[1]->data[i][j];
        }
    }
    //implement the rest of this, need to add zeros to the bottom of R and extend the remaining m-n columns of Q
}
/*
This function is an implementation of the modified Gram-Schmidt algorithm for QR decomposition.
It takes in a matrix A and returns a matrix Q and a matrix R such that A = QR.
It returns a pointer to an array of matrices where the first matrix is Q and the second matrix is R.
*/
matrix **modifiedGrahamSchmidt(matrix *A)//returning Q^T fix this
{
    matrix **QR = malloc(sizeof(matrix *) * 2);
    QR[0] = makeMatrix(A->rows, A->cols);
    QR[1] = makeMatrix(A->cols, A->cols);
    for (int i = 0; i < A->cols; i++)
    {
        //r_ii = ||a_i||
        double r_ii = sqrt(dotProduct(getColumn(A, i), getColumn(A, i)));
        QR[1]->data[i][i] = r_ii;
        //q_i = a_i / r_ii
        for (int j = 0; j < A->rows; j++)
        {
            QR[0]->data[j][i] = A->data[j][i] / r_ii;
        }
        for (int j = i + 1; j < A->cols; j++)
        {
            //r_ij = q_i^T * a_j
            double r_ij = dotProduct(getColumn(QR[0], i), getColumn(A, j));
            QR[1]->data[i][j] = r_ij;
            //a_j = a_j - r_ij * q_i
            for (int k = 0; k < A->rows; k++)
            {
                A->data[k][j] = A->data[k][j] - r_ij * QR[0]->data[k][i];
            }
        }
    }
    return QR;
}
/*
This function is an implementation of the Householder algorithm for QR decomposition.
It takes in a matrix A and returns a matrix W and a matrix R such that WA = R.
It returns a pointer to an array of matrices where the first matrix is W and the second matrix is R.
*/
matrix** householder(matrix* A){
    // This function takes in a matrix A and returns a matrix W and a matrix R such that WA = R
    matrix** WR = malloc(sizeof(matrix*) * 2);
    WR[0] = makeMatrix(A->rows, A->cols);
    WR[1] = copyMatrix(A);
    for(int k = 0; k < A->cols;k++){
        // x = a_k:m,k
        vector *x = makeVector(A->rows-k);
        for(int i = k; i < A->rows; i++){
            x->components[i-k] = A->data[i][k];
        }
        printf("x:\n");
        printVector(x);
        printf("A:\n");
        printMatrix(A);
        printf("\n");
        //w_k = sign(x_1) * ||x|| * e_1 + x
        vector *e = makeVector(A->rows-k);
        e->components[0] = sqrt(dotProduct(x,x));
        for(int i = 1; i < A->rows-k; i++){
            e->components[i] = 0;
        }
        vector *w_k = vectorAdd(scalarMultiplyVector(e,x->components[0]/fabs(x->components[0])), x);
        printf("w_k:\n");
        printVector(w_k);
        //w_k = w_k / ||w_k||
        w_k = makeUnitVector(w_k);
        //A_k:m,k:n = A_k:m,k:n - 2 * w_k * (w_k^T * A_k:m,k:n)
        for(int i = k; i < A->rows; i++){
            for(int j = k; j < A->cols; j++){
                vector* A_k = makeVector(A->rows-k);
                for(int l = k; l < A->rows; l++){
                    A_k->components[l-k] = A->data[l][j];
                }
                //This should be outer product
                WR[1]->data[i][j] -= 2 * w_k->components[i-k] * (dotProduct(w_k, A_k));
            }
        }
        for(int i = k; i < A->rows; i++){
                WR[0]->data[i][k] = w_k->components[i-k];
            }
    }
    return WR;
}
