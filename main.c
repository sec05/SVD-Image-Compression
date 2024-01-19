#include <stdio.h>
#include "math/matrixAlgorithims.h"
#include "math/matrix.h"
#include "image.h"
#define FILEINPUT "/Users/spencerevans-cole/Desktop/Coding/SVD-Image-Compression/images/meAndAbby/meAndAbby.bmp"
#define FILEOUTPUT "/Users/spencerevans-cole/Desktop/Coding/SVD-Image-Compression/images/meAndAbby/meAndAbbyGray.bmp"
int main(int argc, char *argv[]) {
   matrix *A = randomWholeNumberMatrix(2, 5,10);
   matrix* B = copyMatrix(A);
   printMatrix(A);
   /*printf("\n");
   printf("Reduced QR Decomposition:\n");
   matrix** rQR = reducedQR(A);
   printMatrix(rQR[0]);
   printf("\n");
   printMatrix(rQR[1]);
   printf("\n");*/
   printf("Householder QR Decomposition:\n");
   matrix** hQR = householder(B);
   printMatrix(hQR[0]);
   printf("\n");
   printMatrix(hQR[1]);
   printf("\n");
   printf("A = QR:\n");
   printMatrix(matrixMultiply(hQR[0], hQR[1]));
   return 0;
}