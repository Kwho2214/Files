#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main(){
   int n=10;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   //printf("Here\n");
   //printMatrix(stdout, A);
   //printf("here\n");
   
    changeEntry(A, 1, 1, -4);
    changeEntry(A, 1, 2, -2);
    changeEntry(A, 1, 3, 0);
   
   changeEntry(A, 2, 1, -2);
   changeEntry(A, 2, 5, 4);
   

    changeEntry(A, 3, 1, 2);
    changeEntry(A, 2, 2, -2);
    changeEntry(A, 3, 3, 0);
   changeEntry(A, 3, 3, 8);
   changeEntry(A, 3, 2, 6);

   changeEntry(B, 1, 1, -4);
    changeEntry(B, 1, 2, 0);
    changeEntry(B, 2, 1, 0);
    changeEntry(B, 2, 2, -2);
    changeEntry(B, 2, 4, 2);
    changeEntry(B, 3, 1, 2);
    changeEntry(B, 3, 2, 2);
    changeEntry(B, 7, 8, 5);
   
   double x = -2;
   double y = -2;
   printf("diff of x - y = %.1f\n", x - y);


   Matrix T = diff(A, B);
   printMatrix(stdout, A);
   printf("\n");
   printMatrix(stdout, B);
   printf("\n");
   printMatrix(stdout, T);
   //printf("NNZ = %d\n", NNZ(T));
   freeMatrix(&A);
   freeMatrix(&B);
   //freeMatrix(&T);
   return(0);
}

