/***
* Amrita Pasupuleti
* apasupul
* 2024 Winter CSE101 PA2 
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
    int* distance; 
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
    G->distance = calloc(n + 1, sizeof(int));
    G->order = n;
    G->size = 0;
    G->source = NIL;
    for (int i = 1; i <= n; i++) {
        G->parent[i] = NIL;
        G->distance[i] = INF;
        G->adj[i] = newList();
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
    free(G->distance);
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

int getSource(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Error in getSource(): NULL Graph\n");
        exit(EXIT_FAILURE);
    }
    return G->source;
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

int getDist(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Error in getDist(): NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Error in getDist(): vertex out of range\n");
        exit(EXIT_FAILURE);
    }
    return G->distance[u];
}


void getPath(List L, Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Error in getPath(): NULL graph\n");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) == NIL) {
        fprintf(stderr, "Error in getPath(): getSource(G) == NIL\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Error in getPath(): vertex out of range\n");
        exit(EXIT_FAILURE);
    }
    
    
    if (u == getSource(G)) {
        append(L, u);
        return;
    }
    else if (getParent(G, u) == NIL) {
        append(L, NIL);
        return;
    }
    
    getPath(L, G, getParent(G, u));
    append(L, u);
}

void makeNull(Graph G) {
    for (int i = 1; i <= getOrder(G); i++) {
        G->adj[i] = newList();
        strcpy(G->color[i], "white");
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    G->size = 0;
    G->source = NIL;
    G->order = getOrder(G);
    }

    void addEdge(Graph G, int u, int v) {
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
    }

    void addArc(Graph G, int u, int v) {
    List L = G->adj[u];
    moveFront(L);
    while (index(L) != -1 && v > get(L)) {
        moveNext(L);
    }
    if (index(L) == -1) {
        append(L, v);
    }
    else {
        insertBefore(L, v);
    }
    G->size++;
}

void BFS(Graph G, int s) {

    for (int i = 1; i <= getOrder(G); i++) {
      strcpy(G->color[i], "white");
      G->distance[i] = INF;
      G->parent[i] = NIL;
    }

    G->source = s;
    strcpy(G->color[s], "grey");
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List queue = newList();
    append(queue, s);
    while (length(queue) != 0) {
        int u = front(queue);
        deleteFront(queue);

        List L = G->adj[u];
        moveFront(L);

        while (index(L) != -1) {
            int v = get(L);
            if (strcmp(G->color[v], "white") == 0) {
            strcpy(G->color[v], "grey");
            G->distance[v] = G->distance[u] + 1;
            G->parent[v] = u;
            append(queue, v);
            }
            moveNext(L);
        }
        strcpy(G->color[u], "black");
    }
    freeList(&queue);
}

void printGraph(FILE* out, Graph G) {
    if (out == NULL || G == NULL) {
        fprintf(stderr, "Error in printGraph(): NUll graph\n");
        exit(EXIT_FAILURE);
    }
    int i = 1;
    while (i <= getOrder(G)) {
        fprintf(out, "%d: ", i);
        if (length(G->adj[i]) == 0){
            fprintf(out, "\n");
        }

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