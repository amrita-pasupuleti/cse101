/***
* Amrita Pasupuleti
* apasupul
* 2024 Winter CSE101 PA3 
* FindComponents.c
* finds strongly connected components in a graph
***/ 


#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]) {
    // check arguments
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // ----------------------------- STEP 1 -----------------------------
    int n = 0;
    //Read the input file
    FILE* in;
    if ((in = fopen(argv[1], "r")) == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    fscanf(in, " %d", &n);

    // ----------------------------- STEP 2 -----------------------------
    // Assemble a graph object 𝐺 using newGraph() and addArc()
    int u, v = 0;
    Graph G = newGraph(n);
    while (fscanf(in, " %d %d", &u, &v) == 2 && u != 0 && v != 0) {
        addArc(G, u, v);
    }

    // ----------------------------- STEP 3 -----------------------------
    // Print the adjacency list representation of G to the output file
    FILE* out;
    if ((out = fopen(argv[2], "w")) == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    // ----------------------------- STEP 4 -----------------------------
    // Run DFS on 𝐺 and 𝐺𝑇, processing the vertices in the second call by 
    // decreasing finish times from the first call.
    Graph GT = transpose(G);
    List S = newList(), *scc;
    for (int i = 1; i <= n; i++) {
        append(S, i);
    }
    //dfs on both graphs
    DFS(G, S);
    DFS(GT, S);

    // ----------------------------- STEP 5 -----------------------------
    // Determine the strong components of G

    // number of scc
    int x = 0;
    int i = 1;
    while (i <= n) {
        if (getParent(GT, i) == NIL) {
            x++;
        }
        i++;
    }
    // array of lists of scc
    scc = calloc(x, sizeof(List));
    i = 0;
    while (i < x) {
        scc[i] = newList();
        i++;
    }
    //loop through list from last elem
    int compCount = 0;
    moveBack(S);
    while (index(S) >= 0) {
        prepend(scc[compCount], get(S));
        if (getParent(GT, get(S)) == NIL) {
            compCount++;
        }
        movePrev(S);
    }

    // ----------------------------- STEP 6 -----------------------------
    // Print the strong components of 𝐺 to the output file in topologically sorted order
    fprintf(out, "G contains %d strongly connected components:\n", x);

    i = 0;
    while (i < x) {
        fprintf(out, "Component %d: ", i + 1);
        printList(out, scc[i]);
        fprintf(out, "\n");
        freeList(&scc[i]);
        i++;
    }
    

    //close files
    fclose(in);
    fclose(out);
    //free memory
    free(scc);
    freeGraph(&G);
    freeGraph(&GT);
    freeList(&S);

    return 0;
}