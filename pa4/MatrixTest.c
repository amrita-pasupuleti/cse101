/***
* Amrita Pasupuleti
* apasupul
* 2024 Winter CSE101 PA4
* MatrixTest.c
* tests matrix ADT
***/

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main() {
   Matrix A = newMatrix(10);
   Matrix B = newMatrix(10);
   Matrix C, D, E, F, G, H;

   changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
   changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
   changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
   changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
   changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
   changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
   changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
   changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
   changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);

   printf("nonzero in A: %d\n", NNZ(A));
   printf("Matrix A: \n");
   printMatrix(stdout, A);
   printf("\n \n");

   printf("nonzero in B: %d\n", NNZ(B));
   printf("Matrix B: \n");
   printMatrix(stdout, B);
   printf("\n \n");

   printf("testing scalarMult(2,A)\n");
   C = scalarMult(2, A);
   printMatrix(stdout, C);
   printf("\n \n");

   printf("testing sum(A,B)\n");
   D = sum(A, B);
   printMatrix(stdout, D);
   printf("\n \n");

   printf("testing diff(A,A)\n");
   E = diff(A, A);
   printMatrix(stdout, E);
   printf("\n");

   printf("testing transpose(B)\n");
   F = transpose(B);
   printMatrix(stdout, F);
   printf("\n");

   printf("testing product(B,B)\n");
   G = product(B, B);
   printMatrix(stdout, G);
   printf("\n");

   printf("testing copy(A)\n");
   H = copy(A);
   printf("%d\n", NNZ(H));
   printMatrix(stdout, H);
   printf("\n");

   printf("%s\n", equals(A, H)?"true":"false" );
   printf("%s\n", equals(A, B)?"true":"false" );
   printf("%s\n", equals(A, A)?"true":"false" );

    printf("testing makeZero\n");
   makeZero(A);
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);

   return EXIT_SUCCESS;
}
