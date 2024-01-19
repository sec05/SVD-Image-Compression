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
    // This function takes in a matrix A and returns a matrix Q and a matrix R such that A = QR
    // It returns a pointer to an array of matrices where the first matrix is Q and the second matrix is R
    matrix** QR = malloc(sizeof(matrix*) * 2);
    QR[0] = identityMatrix(A->rows, A->rows);
    QR[1] = copyMatrix(A);
    for(int k = 0; k < A->rows;k++){
        vector* x = getColumn(QR[1], k);
        vector* v = makeVector(x->dimension);
        for(int i = 0; i < x->dimension; i++){
            if(i < k){
                v->components[i] = 0;
            }
            else{
                v->components[i] = x->components[i];
            }
        }
        double vNorm = sqrt(dotProduct(v, v));
        
        vector* e = makeVector(v->dimension);
        for(int i = 0; i < e->dimension; i++){
            e->components[i] = 0;
        }
        e->components[k] = 1;

        v = vectorSubtract(v, scalarMultiplyVector(e, vNorm));
        v = makeUnitVector(v);

        matrix* H = identityMatrix(A->rows, A->rows);

        for(int i = 0; i < v->dimension; i++){
            for(int j = 0; j < v->dimension; j++){
                H->data[i][j] = H->data[i][j] - 2 * v->components[i] * v->components[j];
            }
        }

        QR[1] = matrixMultiply(H, QR[1]);
        QR[0] = matrixMultiply(QR[0], transpose(H));
    }
    return QR;
}
