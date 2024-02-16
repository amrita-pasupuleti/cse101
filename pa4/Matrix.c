/***
* Amrita Pasupuleti
* apasupul
* 2024 Winter CSE101 PA4
* Matrix.c
* creates a Matrix ADT
***/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "Matrix.h"
#include "List.h"

typedef struct EntryObj{
	int col;
	double val;
} EntryObj;
typedef EntryObj* Entry;

typedef struct MatrixObj{
	List* rows;
	int size;
	int nnz;
} MatrixObj;

//Constructors, Destructors
//--------------------------------------------------------
Matrix newMatrix(int n){
	Matrix m = malloc(sizeof(MatrixObj));
	m->rows = malloc(sizeof(List)*n);
	int i = 0;
	while (i < n) {
		m->rows[i] = newList();
		i++;
	}
	m->size = n;
	m->nnz = 0;
	return m;
}
void freeMatrix(Matrix* pM){
	if (pM != NULL && *pM != NULL){
		makeZero(*pM);
		int i = 0;
		while (i < (*pM)->size) {
			freeList(&((*pM)->rows[i]));
			i++;
		}
		free((*pM)->rows);
		free(*pM);
	}
}

//helper functions
Entry newEntry(int n, double d){
	Entry e = malloc(sizeof(EntryObj));
	e->col = n;
	e->val = d;
	return e;
}

//Access functions
//--------------------------------------------------------
int size(Matrix M){
	if (M == NULL){
		printf("error in size(): null matrix\n");
		exit(EXIT_FAILURE);
	}
	return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
	if (M == NULL){
		printf("error in NNZ(): null matrix\n");
		exit(EXIT_FAILURE);
	}
	return M->nnz;
}

// equals()
int equals(Matrix A, Matrix B){
	if( A==NULL || B==NULL ){
        printf("Error in equals(): null matrix\n");
        exit(EXIT_FAILURE);
    }

    if (A->size != B->size){
    	return 0;
    }

   	for (int i = 0; i < A->size; i++) {
   		List aa = A->rows[i];
   		List bb = B->rows[i];
	    if (length(aa) != length(bb)){
	    	return 0;
	    }

	    moveFront(aa);
	    moveFront(bb);
	    while(index(aa) >= 0){
	    	Entry entryA = (Entry) get(aa);
	    	Entry entryB = (Entry) get(bb);
			if (entryA->val != entryB->val) {
				return 0;
			}
			else if (entryA->col != entryB->col) {
				return 0;
			}
	    	moveNext(aa);
	    	moveNext(bb);
	    }
   	}
   return 1;
}

//Manipulation procedures
//--------------------------------------------------------
void makeZero(Matrix M){
	if (M == NULL){
		printf("error in makeZero(): null matrix\n");
		exit(EXIT_FAILURE);
	}

	List L;
	for (int i = 0; i < M->size; i++) {
		L = M->rows[i];
		moveFront(L);
		while(index(L) >= 0){
			if (((Entry) get(L)) != NULL) {
				free((Entry) get(L));
			}
			moveNext(L);
		}
		clear(L);
	}

	M->nnz = 0;
}

void changeEntry(Matrix M, int i, int j, double x){
	if (M == NULL){
		printf("error in changeEntry(): null matrix\n");
		exit(EXIT_FAILURE);
	}
	if (1 > i || i > size(M) || 1 > j || j > size(M)){
		printf("error in changeEntry(): row or column out of range\n");
		exit(EXIT_FAILURE);
	} 

	List L = M->rows[i-1];
	if (x == 0) {
		moveFront(L);
		while(index(L) >= 0 && ((Entry)get(L))->col < j){
			moveNext(L);
		}
		if(index(L) >= 0) {
			M->nnz--;
			if (((Entry) get(L)) != NULL) {
				free((Entry) get(L));
			}
			delete(L);
		}
	}
	else {
		if (length(L) == 0){
			append(L, newEntry(j, x));
			M->nnz++;
		} 
		else {
			moveFront(L);
			while(index(L) >= 0 && ((Entry)get(L))->col < j){
				moveNext(L);
			}
			if(index(L) < 0){
				append(L, newEntry(j, x));
				M->nnz++;
			} 
			else if (((Entry) get(L))->col == j){
				((Entry) get(L))->val = x;
			} 
			else {
				insertBefore(L, newEntry(j, x));
				M->nnz++;
			}
		}
	}
}

//Matrix Arithmetic Operations
//--------------------------------------------------------
Matrix copy(Matrix A){
	if (A == NULL){
		printf("error in copy(): null matrix\n");
		exit(EXIT_FAILURE);
	}
	
	Matrix B = newMatrix(A->size);
	B->nnz = A->nnz;

	for (int i = 0; i < A->size;i++) {
		List L = A->rows[i];
		moveFront(L);
		while(index(L) >= 0){
			append(B->rows[i], newEntry(((Entry) get(L))->col, ((Entry) get(L))->val));
			moveNext(L);
		}
	}
	return B;
}

Matrix transpose(Matrix A){
	if (A == NULL){
		printf("error in transpose(): null matrix\n");
		exit(EXIT_FAILURE);
	}
	Matrix B = newMatrix(A->size);
	B->nnz = A->nnz;
	for (int i = 0; i < A->size; i++) {

		List L = A->rows[i];
		moveFront(L);
		while(index(L) >= 0){
			append(B->rows[((Entry) get(L))->col - 1], newEntry(i+1, ((Entry) get(L))->val));
			moveNext(L);
		}
	}
	return B;
}

Matrix scalarMult(double x, Matrix A){
	if (A == NULL){
		printf("error in scalarMult(): null matrix\n");
		exit(EXIT_FAILURE);
	}

	Matrix B = copy(A);
	if (x == 0){
		makeZero(B);
	} 
	else {
		for (int i = 0; i < A->size; i++) {

			List L = B->rows[i];
			moveFront(L);
			while(index(L) >= 0){
				((Entry) get(L))->val *= x;
				moveNext(L);
			}

		}
	}
	return B;
}

Matrix sum(Matrix A, Matrix B){
	if (A == NULL || B == NULL){
		printf("error in sum(): null matrix\n");
		exit(EXIT_FAILURE);
	}
	if (A->size != B->size){
		printf("error in sum(): matrices are not the same size\n");
		exit(EXIT_FAILURE);
	}
	if (A == B){
		return (scalarMult(2, A));
	}

	Matrix M = newMatrix(A->size);
	for (int i = 0; i < A->size; i++) {

		List aa = A->rows[i];
		List bb = B->rows[i];
		List L = M->rows[i];

		moveFront(aa);
		moveFront(bb);
		while(index(aa) >= 0 && index(bb) >= 0){

			Entry entryA = (Entry) get(aa);
			Entry entryB = (Entry) get(bb);
			if (entryA->col < entryB->col){
				M->nnz++;
				append(L, newEntry(entryA->col, entryA->val));
				moveNext(aa);
			} 
			else if (entryA->col > entryB->col){
				M->nnz++;
				append(L, newEntry(entryB->col, entryB->val));
				moveNext(bb);
			} 
			else {
				if (entryA->val + entryB->val != 0){
					M->nnz++;
					append(L, newEntry(entryA->col, entryA->val + entryB->val));
				}
				moveNext(aa);
				moveNext(bb);
			}
		}
		//add remaining entries
		while(index(aa) >= 0){
			M->nnz++;
			append(L, newEntry(((Entry) get(aa))->col, ((Entry) get(aa))->val));
			moveNext(aa);
		}
		while(index(bb) != -1){
			M->nnz++;
			append(L, newEntry(((Entry) get(bb))->col, ((Entry) get(bb))->val));
			moveNext(bb);
		}
	}
	return M;
}

// diff()
Matrix diff(Matrix A, Matrix B){
	if (A == NULL || B == NULL){
		printf("error in diff(): null matrix\n");
		exit(EXIT_FAILURE);
	}
	if (A->size != B->size){
		printf("error in diff(): matrices are different sizes\n");
		exit(EXIT_FAILURE);
	}

	Matrix negatives = scalarMult(-1, B);
	Matrix M = sum(negatives, A);
	freeMatrix(&negatives);
	return M;
}

// product()
Matrix product(Matrix A, Matrix B){
	if (A == NULL || B == NULL){
		printf("Matrix Error: calling product() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if (A->size != B->size){
		printf("Matrix Error: calling product() on invalid precondition\n");
		exit(EXIT_FAILURE);
	}
	Matrix T, M;
	T = transpose(B);
	M = newMatrix(A->size);

	for (int i = 0; i < A->size; ++i) {
		List aa = A->rows[i];
		if (length(aa) != 0){
			for (int j = 0; j < B->size; ++j) {
				List bb = T->rows[j];
				double prdct = 0;

				moveFront(aa);
				moveFront(bb);
				while(index(aa) >= 0 && index(bb) >= 0) {
					Entry entryA = (Entry)get(aa);
					Entry entryB = (Entry)get(bb);
					if (entryA->col > entryB->col){
						moveNext(bb);
					} 
					else if (entryA->col < entryB->col){
						moveNext(aa);
					} 
					else {
						prdct += entryA->val * entryB->val;
						moveNext(aa);
						moveNext(bb);
					}
				}
				if(prdct != 0){
					append(M->rows[i], newEntry(j+1, prdct));
					M->nnz++;
				}
			}
		}
	}

	freeMatrix(&T);
	return M;
}

//printMatrix()
//--------------------------------------------------------
void printMatrix(FILE* out, Matrix M){
	if (M == NULL){
		printf("Matrix Error: calling printMatrix() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < M->size; i++) {
		List L = M->rows[i];
		if(length(L) > 0){
			fprintf(out, "%d:", i+1);
			moveFront(L);
			while(index(L) >= 0){
				fprintf(out, " (%d, %0.1lf)", ((Entry) get(L))->col, ((Entry) get(L))->val);
				moveNext(L);
			}
			fprintf(out, "\n");
		}
	}
}