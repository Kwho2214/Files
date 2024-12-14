#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include"Matrix.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){
	FILE *in, *out;
	char line[MAX_LEN];
	int rows, cols, n = 0;
    double x;

	// check command line for correct number of arguments
	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	
	// open files for reading and writing 
	in = fopen(argv[1], "r");	
	if( in==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}

	out = fopen(argv[2], "w");
	if( out==NULL ){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	//get 1st line of file
    int sizeA, sizeB = 0;
	fscanf(in, "%d %d %d", &n, &sizeA, &sizeB);

    Matrix A = newMatrix(sizeA);
    Matrix B = newMatrix(sizeB);

    //get rows, cols and double for matrix A
    while(fgets(line, MAX_LEN, in) != NULL){
        if(strlen(line) == 0){
            break;
        }
        fscanf(in, "%d %d %lf", &rows, &cols, &x);
        changeEntry(A, rows, cols, x);
    }

    //continue and make the B matrix
    while(fgets(line, MAX_LEN, in) != NULL){
        if(strlen(line) == 0){
            break;
        }
        fscanf(in, "%d %d %lf", &rows, &cols, &x);
        changeEntry(B, rows, cols, x);
    }

    //do the operations
    printf("A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out,A);
    printf("\n");

    printf("B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out,B);
    printf("\n");

    printf("(1.5)*A = \n");
    Matrix s = scalarMult(1.5, A);
    printMatrix(out,s);
    printf("\n");

    printf("A+B =\n");
    Matrix t = sum(A,B);
    printMatrix(out,t);
    printf("\n");

    printf("A+A =\n");
    Matrix tt = sum(A,A);
    printMatrix(out,tt);
    printf("\n");

    printf("B-A =\n");
    Matrix d = diff(B,A);
    printMatrix(out,d);
    printf("\n");

    printf("A-A =\n");
    Matrix N = diff(A,A);
    printMatrix(out,N);
    printf("\n");

    printf("A*B =\n");
    Matrix P = product(A,B);
    printMatrix(out,P);
    printf("\n");

    printf("B*B =\n");
    Matrix Pp = product(B,B);
    printMatrix(out,Pp);
    printf("\n");

    freeMatrix(&s);
    freeMatrix(&t);
    freeMatrix(&tt);
    freeMatrix(&d);
    freeMatrix(&N);
    freeMatrix(&P);
    freeMatrix(&Pp);
    freeMatrix(&A);
    freeMatrix(&B);
    fclose(in);
    fclose(out);
    return(0);
}