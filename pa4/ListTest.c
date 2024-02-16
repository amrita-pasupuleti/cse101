/***
* Amrita Pasupuleti
* apasupul
* 2024 Winter CSE101 PA4
* ListTest.c
* testing file to test list ADT
***/ 

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include"List.h"

int main(int argc, char* argv[]){
   List L = newList();
   printf("New list created.\n");
   printf("Length of list: %d\n", length(L));
   
   //append and prepend
   int a = 1, b = 2, c = 3, d = 4;
   append(L, &a);
   prepend(L, &b);
   append(L, &c);
   prepend(L, &d);
   //printList and lenth
   printf("Print list: ");
   printList(stdout, L);
   printf("Length of list: %d\n", length(L));
   printf("\n");

   //moveFront() and moveBack()
   moveFront(L);
   printf("index after moveFront(): %d\n", index(L));
   moveBack(L);
   printf("index after moveBack(): %d\n", index(L));

   //movePrev() and moveNext()
   movePrev(L);
   printf("index after movePrev(): %d\n", index(L));
   moveNext(L);
   printf("index after moveNext(): %d\n", index(L));
   printf("\n");

   //deleteFront() and deleteBack()
   deleteFront(L);
   printf("List after deleteFront(): ");
   printList(stdout, L);
   printf("\n");
   deleteBack(L);
   printf("List after deleteBack(): ");
   printList(stdout, L);
   printf("\n");

   //clear()
   clear(L);
   printf("List after clear(): ");
   printList(stdout, L);
   printf("\n");

   freeList(&L);

   return 0;
}