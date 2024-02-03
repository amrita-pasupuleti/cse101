/***
* Amrita Pasupuleti
* apasupul
* 2024 Winter CSE101 PA2 
* FindPath.c
* finds shortest paths between vertices using functions from graph ADT
***/ 

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int main(int argc, char* argv[]) {
    //opens input file
    FILE* inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("File %s cannot be opened\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    //opens output file
    FILE* outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        printf("File %s cannot be opened\n", argv[2]);
        exit(EXIT_FAILURE);
    }


    int n, a, b;
    fscanf(inputFile, "%d", &n);
    
    //adds edges based on input file
    Graph G = newGraph(n);
    while (fscanf(inputFile, "%d %d", &a, &b) == 2) {
        if (a == 0 && b == 0) {
            break;
        }
        addEdge(G, a, b);
    }

    //prints graph on output file
    printGraph(outputFile, G);
    while (fscanf(inputFile, "%d %d", &a, &b) == 2) {
        if (a == 0 && b == 0) {
            break;
        }
        BFS(G, a);
        if (getDist(G, b) == INF) {
            fprintf(outputFile, "The distance from %d to %d is infinity\n", a, b);
            fprintf(outputFile, "No %d-%d path exists", a, b);
        } 
        else {
            fprintf(outputFile, "\n");

            int distance = getDist(G, b);
            fprintf(outputFile, "The distance from %d to %d is %d\n", a, b, distance);
            //prints shortest path
            fprintf(outputFile, "A shortest %d-%d path is: ", a, b);
            List L = newList();
            getPath(L, G, b);
            printList(outputFile, L);
            freeList(&L);
        }
        fprintf(outputFile, "\n");
    }
    fclose(inputFile);
    fclose(outputFile);

    freeGraph(&G);

    return 0;
}