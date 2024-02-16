/***
* Amrita Pasupuleti
* apasupul
* 2024 Winter CSE101 PA4
* Sparse.c
* scans an input file to create a Matrix ADT and outputs the results of matrix operations
***/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "Matrix.h"
#include "List.h"

int main(int argc, char* argv[]) {
	FILE *inputFile;
    FILE *outputFile; 

    // checks arguments and files
    if(argc != 3) {
    	fprintf(stderr, "Usage: ./Sparse <input file> <output file>\n");
    	exit(EXIT_FAILURE);
    }
    inputFile = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w");
    if (inputFile == NULL){
    	printf("Unable to open input file %s\n", argv[1]);
    	exit(EXIT_FAILURE);
    }
    if (outputFile == NULL){
    	printf("Unable to open output file %s\n", argv[2]);
    	exit(EXIT_FAILURE);
    }

    //scan info
    int n = 0;
    int a = 0;
    int b = 0;
    fscanf(inputFile, "%d %d %d", &n, &a, &b);

    //scan the entries
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    int row = 0;
    int col = 0;
    double d = 0.0;
    for (int i = 0; i < a; i++) {
    	fscanf(inputFile, "%d %d %lf", &row, &col, &d);
    	changeEntry(A, row, col, d);
    }
    for (int i = 0; i < b; i++) {
    	fscanf(inputFile, "%d %d %lf", &row, &col, &d);
    	changeEntry(B, row, col, d);
    }

    // print matrix A
    fprintf(outputFile, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(outputFile, A);
    fprintf(outputFile, "\n");
    // print matrix B
    fprintf(outputFile, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(outputFile, B);
    fprintf(outputFile, "\n");
    // multiply by 1.5
    fprintf(outputFile, "(1.5)*A =\n");
    Matrix C = scalarMult(1.5, A);
    printMatrix(outputFile, C);
    fprintf(outputFile, "\n");
    // A + B
    fprintf(outputFile, "A+B =\n");
    Matrix D = sum(A, B);
    printMatrix(outputFile, D);
    fprintf(outputFile, "\n");
    // A + A
    fprintf(outputFile, "A+A =\n");
    Matrix E = sum(A, A);
    printMatrix(outputFile, E);
    fprintf(outputFile, "\n");
    // B - A
    fprintf(outputFile, "B-A =\n");
    Matrix F = diff(B, A);
    printMatrix(outputFile, F);
    fprintf(outputFile, "\n");
    // A - A
    fprintf(outputFile, "A-A =\n");
    Matrix G = diff(A, A);
    printMatrix(outputFile, G);
    fprintf(outputFile, "\n");
    // transpose of A
    fprintf(outputFile, "Transpose(A) =\n");
    Matrix H = transpose(A);
    printMatrix(outputFile, H);
    fprintf(outputFile, "\n");
    // A*B
    fprintf(outputFile, "A*B =\n");
    Matrix I = product(A, B);
    printMatrix(outputFile, I);
    fprintf(outputFile, "\n");
    // B*B
    fprintf(outputFile, "B*B =\n");
    Matrix J = product(B, B);
    printMatrix(outputFile, J);

    fclose(inputFile);
    fclose(outputFile);

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);

	return 0;
}
