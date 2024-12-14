#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
  List A = newList();
    prepend(A, 34);
    printf("Index = %d\n", index(A));
    prepend(A, 4);
    prepend(A, 354);
    prepend(A, 3674);
    moveBack(A);
    printf("Index = %d\n", index(A));
    insertBefore(A, 435);
    if (index(A) != 4)
      return 1;
    prepend(A, 324);
    prepend(A, 33464);
    prepend(A, 3498);
    moveFront(A);
    insertBefore(A, 67);
    if (index(A) != 1) {
      printf("Error 2\n");
      return 2;
    }
    return 0;

    freeList(&A);
}
