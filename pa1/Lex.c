/***
* Amrita Pasupuleti
* apasupul
* 2024 Winter CSE101 PA1 
* Lex.c
* uses List.c to sort lines from an input file alphabetically
***/ 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

//free memory from array function
void freeArray(char **array, int size) {
    for (int i = 0; i < size; i++) {
        free(array[i]);
    }
    free(array);
}


int main(int argc, char **argv) {
    //check arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    //count lines in input file
    char *filename = argv[1];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "File '%s' could not be opened. \n", filename);
        exit(1);
    }
    int count = 0;
    char line[1024];
    while (fgets(line, 1024, fp) != NULL) {
        count++;
    }
    fclose(fp);

    //allocate memory for array of lines
    char **lines = malloc(count * sizeof(char *));
    if (lines == NULL) {
        fprintf(stderr, "Error: memory allocation for lines array failed\n");
        exit(1);
    }

    //places lines from input file into array
    FILE *fp1 = fopen(filename, "r");
    if (fp1 == NULL) {
        fprintf(stderr, "File '%s' could not be opened. \n", filename);
        exit(1);
    }
    int i = 0;
    while (fgets(line, 1024, fp1) != NULL && i < count) {
        lines[i] = malloc((strlen(line) + 1) * sizeof(char));
        strcpy(lines[i], line);
        i++;
    }
    fclose(fp1);
    

    //create list of indices
    List L = newList();
    append(L, 0);
    for (int i = 1; i < count; i++) {
        moveFront(L);
        while (index(L) >= 0 && strcmp(lines[i], lines[get(L)]) > 0) {
            moveNext(L);
        }
        if (index(L) >= 0) {
            insertBefore(L, i);
        } 
        else {
            append(L, i);
        }
    }

    //write the sorted lines to the output file
    FILE *out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "File '%s' could not be opened for writing. \n", argv[2]);
        exit(1);
    }
    //move cursor to the front
    moveFront(L);
    //print each line
    while (index(L) >= 0) {
        fprintf(out, "%s", lines[get(L)]);
        moveNext(L);
    }
    fclose(out);

    //free list
    freeList(&L);

    //free array
    freeArray(lines, count);

    return 0;
}
