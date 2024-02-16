/***
* Amrita Pasupuleti
* apasupul
* 2024 Winter CSE101 PA3
* GraphTest.c
* tests graph ADT from Graph.C
***/ 

#include<stdio.h>
#include<stdlib.h>

#include"Graph.h"
#include "List.h"

int main(int argc, char* argv[]){

   printf("Now testing graph functions . . . \n");
   // Add tests for getOrder and getSize
   Graph a = newGraph(5);
   printf("Order of a: %d\n", getOrder(a)); // Expected: 5
   printf("Size of a: %d\n", getSize(a));   // Expected: 0

   // Add tests for addArc and addEdge
   addArc(a, 1, 2);
   addArc(a, 2, 3);
   addEdge(a, 4, 5);
   printf("\nGraph after adding arcs and edges:\n");
   printGraph(stdout, a);

   // Add tests for getParent, getDiscover, and getFinish
   printf("\nParent of vertex 2: %d\n", getParent(a, 2)); // Expected: 0
   printf("Discover time of vertex 3: %d\n", getDiscover(a, 3)); // Expected: UNDEF
   printf("Finish time of vertex 1: %d\n", getFinish(a, 1)); // Expected: UNDEF

   // Add tests for DFS
   printf("\nPerforming DFS on the graph:\n");
   List N = newList();
   append(N, 1);
   append(N, 2);
   append(N, 3);
   append(N, 4);
   append(N, 5);
   DFS(a, N);
   printf("Graph after DFS:\n");
   printGraph(stdout, a);

   // Add tests for transpose and copyGraph
   Graph b = transpose(a);
   Graph c = copyGraph(a);
   printf("\nTranspose of a:\n");
   printGraph(stdout, b);
   printf("\nCopy of a:\n");
   printGraph(stdout, c);

   // Free allocated memory
   freeList(&N);
   freeGraph(&a);
   freeGraph(&b);
   freeGraph(&c);
   

   printf("\n \n Now testing given GraphClent.c . . . \n \n");

   int i, n=8;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);
   printGraph(stdout, G);

   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   return(0);
}
