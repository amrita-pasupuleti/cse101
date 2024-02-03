/***
* Amrita Pasupuleti
* apasupul
* 2024 Winter CSE101 PA1 
* ListTest.c
* tests functions from List.c and List.h
***/ 


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){

    //test list construction
    printf("Creating lists A and B:\n");
    List A = newList();
    List B = newList();
    int i;
    for(i=1; i<=5; i++){
        append(A,i);
        prepend(B,i);
    }
    printList(stdout,A); //1 2 3 4 5
    printList(stdout,B); //5 4 3 2 1

    //test cursor
    printf("Testing cursor A and B:\n");
    for(moveFront(A); index(A)>=0; moveNext(A)){
        printf("%d ", get(A));
    }
    printf("\n");
    for(moveBack(B); index(B)>=0; movePrev(B)){
        printf("%d ", get(B));
    }
    printf("\n");

    printf("Testing copyList(A) on list C:\n");
    List C = copyList(A);
    printf("A=B is \n");
    printf("%s\n", equals(A,B)?"true":"false");
    printf("B=C is \n");
    printf("%s\n", equals(B,C)?"true":"false");
    printf("C=A is \n");
    printf("%s\n", equals(C,A)?"true":"false");


//  testing move functions
    moveFront(A); //at index 0
    moveNext(A);  //at index 1
    insertBefore(A, -1);            // at index 2
    printList(stdout,A);
    printf("%d %d \n", get(A), index(A));

    moveNext(A); // at index 3
    printList(stdout,A);
    printf("%d %d \n", get(A), index(A));


    insertAfter(A, -2);
    for(i=0; i<3; i++) movePrev(A); // at index 0
    printList(stdout,A);
    printf("%d %d \n \n", get(A), index(A));
    

    //testing delete and clear
    printf("testing delete and clear \n");
    delete(A);
    printList(stdout,A);
    printf("%d\n", length(A));
    clear(A);
    printf("%d\n", length(A));

    //testing with one element
    List D = newList();
    append(D,1);
    moveFront(D);
    printList(stdout,D);
    delete(D);
    
    freeList(&A);
    freeList(&B);
    freeList(&C);
    freeList(&D);

    return(0);
}
