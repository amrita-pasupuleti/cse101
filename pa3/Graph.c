/***
* Amrita Pasupuleti
* apasupul
* 2024 Winter CSE101 PA3 
* Graph.c
* creates a Graph ADT
***/ 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Graph.h"
#include "List.h"

typedef struct GraphObj {   
    List* adj;    
    char (*color)[10];   

    int* parent;  
    int* discover; 
    int* finish;

    int order;     
    int size;      
    int source;     
} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n) {         
    Graph G = malloc(sizeof(GraphObj));
    G->adj = calloc(n + 1, sizeof(List));
    G->color = calloc(n + 1, sizeof(char[10]));
    G->parent = calloc(n + 1, sizeof(int));
    G->discover = malloc((n+1) * sizeof(int));
    G->finish = malloc((n+1) * sizeof(int));
    G->order = n;
    G->size = 0;
    G->source = NIL;
    for (int i = 1; i <= n; i++) {
        G->parent[i] = NIL;
        G->adj[i] = newList();
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
        strcpy(G->color[i], "white");
    }
    return G;
}

void freeGraph(Graph* pG) {  
    if (pG == NULL || *pG == NULL) {
        return;
    }
    Graph G = *pG;
    for (int i = 1; i <= G->order; i++) {
        freeList(&(G->adj[i]));
    }
    free(G->adj);
    free(G->color);
    free(G->parent);
    free(G->discover);
    free(G->finish);
    free(*pG);
    *pG = NULL;
}

/*** Access functions ***/
int getOrder(Graph G) {   
    if (G == NULL) {
        fprintf(stderr, "Error in getOrder(): NULL Graph\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}
 
int getSize(Graph G) { 
    if (G == NULL) {
        fprintf(stderr, "Error in getSize(): NULL Graph\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

int getParent(Graph G, int u) {   
    if (G == NULL) {
        fprintf(stderr, "Error in getParent(): NULL Graph\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Error in getParent(): vertex out of range\n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}

int getDiscover(Graph G, int u) {  
    if (G == NULL) {
        fprintf(stderr, "Error in getDiscover(): NULL Graph\n");
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Error in getDiscover(): vertex out of range\n");
        exit(EXIT_FAILURE);
    }
    return G->discover[u];
}

int getFinish (Graph G, int u) {  
    if (G == NULL) {
        fprintf(stderr, "Error in getFinish(): NULL Graph\n");
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Error in getFinish(): vertex out of range\n");
        exit(EXIT_FAILURE);
    }
    return G->finish[u];
}

/*** Manipulation Procedures ***/
void addArc(Graph G, int u, int v) { 
    if (G == NULL) {
        fprintf(stderr, "Error in addArc(): NULL Graph\n");
    }
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        fprintf(stderr, "Error in addArc(): vertex out of range\n");
        exit(EXIT_FAILURE);
    }

    List L = G->adj[u];

    if (length(L) == 0){
        append(L, v);
    }   
    else {
        moveFront(L);
        while (index(L) >= 0) { 
            if (v == get(L)) {
                return;
            }
            if (v < get(L)) {
                insertBefore(L, v);
                break;
            }
            moveNext(L);
        }
        if (index(L) < 0) {
            append(L, v);
        }
    }
    G->size++;
}

void addEdge(Graph G, int u, int v) { 
   addArc(G, u, v);
   addArc(G, v, u);
   G->size--;
}

void DFS(Graph G, List S) { 
    /*Given Pseudo Code
    for all x in V(G)
      color[x] = white 
      p[x] = nil 
    time = 0
    for all x in V(G)  // main loop of DFS
      if color[x] == white 
         Visit(x) */

    for(int i = 0; i <= getOrder(G); i++){
        strcpy(G->color[i], "white");
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    
    int time = 0;
    List temp = copyList(S);
    clear(S);
    moveFront(temp);
    while(index(temp) >= 0){
        int x = get(temp); //vertex
        if(strcmp(G->color[x], "white") == 0){
            visit(G, x, &time, S);
        }
        moveNext(temp);
    }
    freeList(&temp);
}

void visit(Graph G, int x, int *time, List L){ 
    G->discover[x] = ++(*time);
    strcpy(G->color[x], "grey");

    List N = G->adj[x];
    moveFront(N);
    while (index(N) >= 0) {
        int y = get(N);
        if(strcmp(G->color[y], "white") == 0){
            G->parent[y] = x;
            visit(G, y, time, L);
        }
        moveNext(N);
    }
    strcpy(G->color[x], "black");
    G->finish[x] = ++(*time);
    prepend(L, x); 
}

/*** Other functions ***/
Graph transpose(Graph G) { 
    Graph T = newGraph(getOrder(G));
    for (int u = 1; u <= getOrder(G); u++) {
        List adjList = G->adj[u];
        moveFront(adjList);
        while (index(adjList) >= 0) {
            addArc(T, get(adjList), u); 
            moveNext(adjList);
        }
    }
    return T;
}

Graph copyGraph(Graph G) { 

    Graph C = newGraph(getOrder(G));
    for (int u = 1; u <= getOrder(G); u++) {

        List adjList = G->adj[u];
        moveFront(adjList);

        while (index(adjList) != -1) {
            addArc(C, u, get(adjList));
            moveNext(adjList);
        }

    }
    return C;
}
void printGraph(FILE* out, Graph G) { 
    if (out == NULL || G == NULL) {
        fprintf(stderr, "Error in printGraph(): NUll graph\n");
        exit(EXIT_FAILURE);
    }
    int i = 1;
    while (i <= getOrder(G)) {
        fprintf(out, "%d: ", i);
        

        List adjList = G->adj[i];
        int listLength = length(adjList);
        moveFront(adjList);

        for (int j = 0; j < listLength; j++) {
            fprintf(out, "%d", get(adjList));
            if (j < listLength - 1) {
                fprintf(out, " ");
            }
            moveNext(adjList);
        }

        fprintf(out, "\n");
        i++;

    }
}