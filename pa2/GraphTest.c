/***
* Amrita Pasupuleti
* apasupul
* 2024 Winter CSE101 PA2 
* GraphTest.c
* tests graph ADT
***/ 

#include<stdio.h>
#include<stdlib.h>

#include"Graph.h"

void testRes(int success) {
    if (success) {
        printf("passes test\n"); 
    } else {
        printf("fails test\n"); 
    }
}

int main(int argc, char* argv[]){

   printf("Now testing Graph.c . . . \n");
   Graph H = NULL; 
   List L = newList(); 

   printf("Create graph with 10 vertices\n");
   H = newGraph(10); 
   testRes(getOrder(H) == 10); 

   printf("Adding 5 edges to graph, checking size\n");
   addEdge(H, 1, 2); 
   addEdge(H, 2, 3);
   addEdge(H, 3, 4);
   addEdge(H, 4, 5);
   addEdge(H, 5, 1);
   testRes(getSize(H) == 5 && getDist(H, 4) == -1 && getParent(H, 4) == NIL); 

   printf("Checking source vertex 2\n");
   BFS(H, 2); 
   testRes(getSource(H) == 2); 

   printf("Checking path\n");
   getPath(L, H, 3); 
   testRes(front(L) == 2 && back(L) == 3 && length(L) == 2); 

   printf("Checking distance\n");
   testRes(getDist(H, 3) == 1); 

   printf("Freeing memory\n");
   freeGraph(&H); 
   freeList(&L); 

   testRes(1); 

   printf("\n \n Now testing given GraphClent.c . . . \n");
   int i, s, max, min, d, n=35;
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
   Graph G = NULL;

   // Build graph G 
   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);

   // Print adjacency list representation of G
   printGraph(stdout, G);

   // Calculate the eccentricity of each vertex 
   for(s=1; s<=n; s++){
      BFS(G, s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }

   // Determine the Radius and Diameter of G, as well as the Central and 
   // Peripheral vertices.
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveFront(E);
   moveNext(E);
   for(i=2; i<=n; i++){
      d = get(E);
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }

   // Print results 
   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");

   // Free objects 
   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeGraph(&G);

   return(0);
}