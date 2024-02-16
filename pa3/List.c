/***
* Amrita Pasupuleti
* apasupul
* 2024 Winter CSE101 PA3
* List.c
* creates List ADT
***/ 

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"

typedef struct NodeObj *Node;
typedef struct NodeObj {
   ListElement data;
   Node next;
   Node prev;
} NodeObj;

typedef struct ListObj {
   Node front;
   Node back;
   Node cursor;
   int length;
} ListObj;

//Constructors, Destructors
//--------------------------------------------------------
List newList () {
   List L;
   L = malloc(sizeof(ListObj));
   assert(L!=NULL);
   L->front = L->back = NULL;
   L->cursor = NULL;
   L->length = 0;
   return(L);
}

void freeList(List* pL){
    if (pL != NULL && *pL != NULL) {
      Node current = (*pL)->front;
      Node next;
      
      while (current != NULL) {
         next = current->next;
         free(current);
         current = next;
      }

      free(*pL);
      *pL = NULL;

   }
}

Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   assert(N != NULL);
   N->data = data;
   N->next = NULL;
   return(N);
}

//Access Functions
//--------------------------------------------------------
int length(List L){
   if (L==NULL) {
       printf("List Error in length(): accessing NULL list\n");
      exit(EXIT_FAILURE);
   }
   return(L->length);
}

int index(List L) {
    int i = 0;
    Node current = L->front;
    while (current != NULL) {
        if (current == L->cursor) {
            return i; 
        }
        current = current->next;
        i++;
    }
    return -1; 
}


int front(List L) {
   if (L==NULL) {
      printf("List Error in front(): accessing NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (L->length <= 0) {
      printf("List error in front(): length <= 0\n");
      exit(EXIT_FAILURE);
   }
   return(L->front->data);
}

int back (List L) {
   if (L==NULL) {
      printf("List Error in back(): accessing NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (L->length <= 0) {
      printf("List error in back(): empty list\n");
      exit(EXIT_FAILURE);
   }
   return(L->back->data);
}

int get (List L) {
   if (L==NULL) {
      printf("List Error: accessing NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (L->length <= 0) {
      printf("List error: calling front() on empty list\n");
      exit(EXIT_FAILURE);
   }
   if (index(L) < 0) {
      printf("List error: index is less than 0\n");
      exit(EXIT_FAILURE);
      return(-1);
   }
   return(L->cursor->data);
}

bool equals(List A, List B) {
   if (A == NULL || B == NULL) {
      printf("List Error,equals(): comparing NULL lists\n");
      exit(EXIT_FAILURE);
   }

   if (length(A) != length(B)) {
      return false; 
   }

   Node nodeA = A->front;
   Node nodeB = B->front;

   while (nodeA != NULL) {
      if (nodeA->data != nodeB->data) {
         return false; // Data mismatch
      }
      nodeA = nodeA->next;
      nodeB = nodeB->next;
   }

   return true; 
}

//Manipulation Functions
//------------------------------------------------------------------------
void append(List L, int x) {
   if (L == NULL) {
      printf("List Error in append(): appending to NULL list\n");
      exit(EXIT_FAILURE);
   }

   Node newNode = malloc(sizeof(NodeObj));
   if (newNode == NULL) {
      printf("List Error in append(): memory allocation error\n");
      exit(EXIT_FAILURE);
   }

   newNode->data = x;
   newNode->next = NULL;

   if (L->length == 0) {
      L->front = L->back = newNode;
   } 
   else {
      L->back->next = newNode;
      newNode->prev = L->back;
      L->back = newNode;
   }

   L->length++;
}

void prepend(List L, ListElement x) {
    Node newNode = malloc(sizeof(struct NodeObj));
    if (newNode == NULL) {
        fprintf(stderr, "List error in prepend(): Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    
    newNode->data = x;
    newNode->next = L->front;
    newNode->prev = NULL;

    if (L->front == NULL) {
        //if the list is empty, both back and front is newNode
        L->front = newNode;
        L->back = newNode;
    } 
    else {
        L->front->prev = newNode;
        L->front = newNode;
    }

    L->length++;
}


void clear(List L) {
   if (L == NULL) {
      printf("List error in clear()\n");
      exit(EXIT_FAILURE);
   }

   Node current = L->front;
   Node next;

   while (current != NULL) {
      next = current->next;
      free(current);
      current = next;
   }

   L->front = L->back = L->cursor = NULL;
   L->length = 0;
}

void set(List L, int x) {
   if (L == NULL) {
      printf("List error in set(): null list\n");
      exit(EXIT_FAILURE);
   }

   if (L->length <= 0 || index(L) < 0) {
      printf("List error in set(): empty list\n");
      exit(EXIT_FAILURE);
   }

   L->cursor->data = x;
}

void moveFront(List L) {
   if (L == NULL) {
      printf("List error in moveFront(): NULL list\n");
      exit(EXIT_FAILURE);
   }

   if (L->length > 0) {
      L->cursor = L->front;
   }
}

void moveBack(List L) {
   if (L == NULL) {
      printf("List error in moveBack(): NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (L->length > 0) {
      L->cursor = L->back;
   }
}

void movePrev(List L) {
   if (L == NULL) {
      printf("List error in movePrev(): NULL list\n");
      exit(EXIT_FAILURE);
   }

   if (L->cursor != NULL) {
      if (L->cursor != L->front) {
         L->cursor = L->cursor->prev;
      } 
      else {
         L->cursor = NULL;
      }
   }
}

void moveNext(List L) {
   if (L == NULL) {
      printf("List error in moveNext(): NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (L->cursor != NULL) {
      if (L->cursor != L->back) {
         L->cursor = L->cursor->next;
      } 
      else {
         L->cursor = NULL;
      }
   }
}

void insertBefore(List L, int x) {
   if (L == NULL) {
      printf("List Error in insertBefore(): NULL list\n");
      exit(EXIT_FAILURE);
   }

   if (L->length <= 0 || index(L) < 0) {
      printf("List error in insertBefore(): L->length <= 0 || index(L) < 0\n");
      exit(EXIT_FAILURE);
   }

   Node N = newNode(x);
   if (index(L) == 0) {
      L->front->prev = N;
      N->next = L->front;
      L->front = N;
   } 
   else {
      N->prev = L->cursor->prev;
      L->cursor->prev->next = N;
      N->next = L->cursor;
      L->cursor->prev = N;
   }
   L->length++;
}

void insertAfter(List L, int x) {
   if (L == NULL) {
      printf("List Error: inserting after cursor in NULL list\n");
      exit(EXIT_FAILURE);
   }

   if (L->length <= 0 || index(L) < 0) {
      printf("List error: invalid state for insertAfter()\n");
      exit(EXIT_FAILURE);
   }

   Node newNode = malloc(sizeof(NodeObj));
   if (newNode == NULL) {
      printf("Memory allocation error\n");
      exit(EXIT_FAILURE);
   }

   newNode->data = x;

   if (L->cursor->next != NULL) {
      newNode->prev = L->cursor;
      newNode->next = L->cursor->next;
      L->cursor->next->prev = newNode;
      L->cursor->next = newNode;
   } else {
      newNode->prev = L->cursor;
      newNode->next = NULL;
      L->cursor->next = newNode;
      L->back = newNode;
   }

   L->length++;
}

void deleteFront(List L) {
   if (L == NULL) {
      printf("List Error: deleting front element in NULL list\n");
      exit(EXIT_FAILURE);
   }

   if (L->length <= 0) {
      printf("List error: deleting front element from empty list\n");
      exit(EXIT_FAILURE);
   }

   Node temp = L->front;
   if (L->length == 1) {
      L->front = L->back = L->cursor = NULL;
   } else {
      L->front = L->front->next;
      L->front->prev = NULL;
      if (L->cursor == temp) {
         L->cursor = NULL;
      }
   }

   free(temp);
   L->length--;
}

void deleteBack(List L) {
   if (L == NULL) {
      printf("List Error: deleting back element in NULL list\n");
      exit(EXIT_FAILURE);
   }

   if (L->length <= 0) {
      printf("List error: deleting back element from empty list\n");
      exit(EXIT_FAILURE);
   }

   Node temp = L->back;
   if (L->length == 1) {
      L->front = L->back = L->cursor = NULL;
   } else {
      L->back = L->back->prev;
      L->back->next = NULL;
      if (L->cursor == temp) {
         L->cursor = NULL;
      }
   }

   free(temp);
   L->length--;
}

void delete(List L) {
    if (length(L) <= 0 || index(L) < 0) {
        fprintf(stderr, "Error: Preconditions not met for delete()\n");
        exit(EXIT_FAILURE);
    }
    Node current = L->cursor;

    if (L->length==1) {
        L->front = NULL;
        L->back = NULL;
    } 
    else if (current == L->front) {
        L->front = current->next;
        L->front->prev = NULL;
    } 
    else if (current == L->back) {
        L->back = current->prev;
        L->back->next = NULL;
    } 
    else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    free(current);
    L->cursor = NULL;
    L->length--;
}



//Other functions
//------------------------------------------------------------------------
void printList(FILE* out, List L) {
   if (out == NULL || L == NULL) {
      printf("List Error in printList(): NULL file or NULL list\n");
      exit(EXIT_FAILURE);
   }

   Node current = L->front;

   while (current != NULL) {
      fprintf(out, "%d ", current->data);
      current = current->next;
   }

   fprintf(out, "\n");
}

List copyList(List L) {
   if (L == NULL) {
      printf("List Error in copyList(): NULL list\n");
      exit(EXIT_FAILURE);
   }

   List newListCopy = newList();

   Node current = L->front;

   while (current != NULL) {
      append(newListCopy, current->data);
      current = current->next;
   }

   return newListCopy;
}
