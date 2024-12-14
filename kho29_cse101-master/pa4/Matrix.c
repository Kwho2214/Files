#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>
#include"Matrix.h"

typedef struct EntryObj* Entry;

typedef struct EntryObj{
    int cols;
    double value;
}EntryObj;

Entry newEntry(int cols, double value){
    Entry E = malloc(sizeof(EntryObj));
    assert(E != NULL);
    E->cols = cols;
    E->value = value;
    return(E);
}

void freeEntry(Entry *E){
    if(E != NULL && *E != NULL){
        free(*E);
        *E = NULL;
    }
}

typedef struct MatrixObj{
    int size;
    int NNZ;
    //may rename to row
    List* array;
}MatrixObj;

Matrix newMatrix(int n){
    Matrix M = malloc(sizeof(MatrixObj));
    assert(M != NULL);
    
    M->array = calloc(n+1, sizeof(List*));
    for(int i = 1; i <= n; i++){
        M->array[i] = newList();
    }
    M->size = n;
    M->NNZ = 0;
    return(M);
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    if(*pM != NULL && pM != NULL){
        for(int i = 1; i <= size((*pM)); i++){
            freeList(&(*pM)->array[i]);
        }
    }
    free((*pM)->array);
    free(*pM);
    *pM = NULL;
}

// size()
// Return the size of square Matrix M.
int size(Matrix M) {
    if (M != NULL){
        return(M->size);
    }
    else {
        printf("Error, Matrix is NULL, at size()");
        exit(1);
    }
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
    if (M != NULL){
        return(M->NNZ);
    }
    else {
        printf("Error, Matrix NULL while calling NNZ");
        exit(1);
    }
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
    if (A == NULL || B == NULL){
        printf("Error, Matrix is NULL, at equals()");
        exit(1);
    }
    if(size(A) != size(B)){
        return(0);
    }
    if(A->NNZ != B->NNZ){
        return(0);
    }
    for(int i = 1; i <= size(A); i++){
        if(length(A->array[i]) == 0 && length(B->array[i]) == 0){
            continue;
        }
        if(length(A->array[i]) == length(B->array[i])){
            while(index(A->array[i]) >= 0 && index(B->array[i]) >= 0){
                moveFront(A->array[i]);
                moveFront(B->array[i]);
                Entry x = (Entry)get(A->array[i]);
                Entry y = (Entry)get(B->array[i]);
                if(x->value != 0 && y->value != 0) {
                    if (x->cols != y->cols){
                        return(0);
                    }   
                    if (x->value != y->value){
                        return(0);
                    }
                }
                moveNext(A->array[i]);
                moveNext(B->array[i]);
            }
        }
    }
    return(1);
}

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
    if (M != NULL){
        for(int i = 1; i<=size(M); i++){
            clear(M->array[i]);
            M->NNZ = 0;
            moveNext(M->array[i]);
        }
    }
    else {
        printf("Error, Matrix is NULL, while calling makeZero()");
        exit(1);
    }
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
    if(M == NULL){
        printf("ERROR, matrix is NULL in changeEntry");
        exit(1);
    }
    if(i < 1 && i >= size(M) && j < 1 && j >= size(M)){
        printf("Error, i,j is less than 1 or bigger than size(M) at changeEntry");
        exit(1);
    }
    List row = M->array[i];
    if(length(row) == 0){
        if(x != 0){
            Entry N = newEntry(j, x);
            append(row, N);
            M->NNZ++;
            return;
        }
    }
    moveFront(row);
    while(index(row) >= 0){
        Entry entry = (Entry)get(row);
        if(entry->cols == j){
            if(x == 0){
                freeEntry(&entry);
                delete(row);
                M->NNZ--;
                return;
            }
            else{
                entry->value = x;
                return;
            }
        }
        else if(entry->cols > j){
            if(x != 0){
                Entry J = newEntry(j, x);
                insertBefore(row, J);
                M->NNZ++;
                return;
            }
        }
        moveNext(row);
    }
    if(x != 0){
        Entry E = newEntry(j, x);
        append(row, E);
        M->NNZ++;
    }
}

// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
    if(A == NULL){
        printf("ERROR, matrix is NULL in MatrixCopy()");
        exit(1);
    }
    int s = size(A);
    Matrix B = newMatrix(s);
    for(int i = 1; i <= s; i++){
        moveFront(A->array[i]);
        while(index(A->array[i]) >= 0){
            Entry temp = (Entry)get(A->array[i]);
            if(temp->value != 0){
                changeEntry(B, i, temp->cols, temp->value);
            }
            moveNext(A->array[i]);
        }
    }
    return(B);
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
    if(A == NULL){
        printf("ERROR, matrix is NULL in Transpose()");
        exit(1);
    }
    int n = size(A);
    Matrix B = newMatrix(n);
    for(int i = 1; i <= n; i++){
        moveFront(A->array[i]);
        while(index(A->array[i]) >= 0){
            Entry E = (Entry)get(A->array[i]);
            if(E->value != 0){
                changeEntry(B, E->cols, i, E->value);
            }
            moveNext(A->array[i]);
        }
    }
    return(B);
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
    if(A == NULL){
        printf("ERROR, matrix is NULL in scalarMult()");
        exit(1);
    }
    int n = size(A);
    Matrix new = newMatrix(n);
    for(int i = 1; i <= n; i++){
        moveFront(A->array[i]);
        while(index(A->array[i]) >= 0) {
            Entry E = (Entry)get(A->array[i]);
            if(E->value != 0){
                changeEntry(new, i, E->cols, x * E->value);
            }
            moveNext(A->array[i]);
        }
    }
    return(new);
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
    if(A == NULL && B == NULL){
        printf("ERROR, matrix is NULL in sum()");
        exit(1);
    }
    if(size(A) != size(B)){
        printf("Error, size(A) does not equal to size(B) in sum()");
        exit(1);
    }
    if(A == B){
        return(scalarMult(2, A));
    }
    Matrix temp = newMatrix(size(A));

    for(int i = 1; i <= size(A); i++){
        moveFront(A->array[i]);
        moveFront(B->array[i]);

        while(index(A->array[i]) >= 0 && index(B->array[i]) >= 0){
            Entry a = (Entry)get(A->array[i]);
            Entry b = (Entry)get(B->array[i]);
            
            //if stuff still in A add it in to temp->array
            if(a->cols < b->cols){
                Entry n = newEntry(a->cols, a->value);
                append(temp->array[i], n);
                temp->NNZ++;
                moveNext(A->array[i]);
                
            }
            //if stuff still in B add it in to temp->array
            else if(a->cols > b->cols){
                Entry n = newEntry(b->cols, b->value);
                append(temp->array[i], n);
                temp->NNZ++;
                moveNext(B->array[i]);

            }else if(a->cols == b->cols){
                if(a->value + b->value != 0){
                    Entry n = newEntry(a->cols, a->value + b->value);
                    append(temp->array[i], n);
                }
                moveNext(A->array[i]);
                moveNext(B->array[i]);
            }
        }
        if(index(A->array[i]) >= 0){
            Entry new = (Entry)get(A->array[i]);
            append(temp->array[i], new);
            temp->NNZ++;
            moveNext(A->array[i]);
        }
        else if(index(B->array[i]) >= 0){
            Entry nnn = (Entry)get(B->array[i]);
            append(temp->array[i], nnn);
            temp->NNZ++;
            moveNext(B->array[i]);
        }
    }
    return(temp);
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
    if(A == NULL && B == NULL){
        printf("ERROR, matrix is NULL in diff()");
        exit(1);
    }
    if (size(A) != size(B)){
        printf("Error, size(A) does not equal to size(B) in diff()");
        exit(1);
    }
    if(equals(A,B) == 0){
        makeZero(A);
        return(A);
    }
    Matrix temp = newMatrix(size(A));

    for(int i = 1; i <= size(A); i++){
        moveFront(A->array[i]);
        moveFront(B->array[i]);

        while(index(A->array[i]) >= 0 && index(B->array[i]) >= 0){
            Entry a = (Entry)get(A->array[i]);
            Entry b = (Entry)get(B->array[i]);
            
            //if stuff still in A add it in to temp->array
            if(a->cols < b->cols){
                Entry n = newEntry(a->cols, a->value);
                append(temp->array[i], n);
                temp->NNZ++;
                moveNext(A->array[i]);
            }

            //if stuff still in B add it in to temp->array
            else if(a->cols > b->cols){
                Entry n = newEntry(b->cols, -1*b->value);
                append(temp->array[i], n);
                temp->NNZ++;
                moveNext(B->array[i]);

            }else if(a->cols == b->cols){
                if(a->value - b->value != 0){
                    Entry n = newEntry(a->cols, a->value - b->value);
                    append(temp->array[i], n);
                    if(a->value - b->value == 0){
                        temp->NNZ--;
                    }
                }
                moveNext(A->array[i]);
                moveNext(B->array[i]);
            }
        }
        if(index(A->array[i]) >= 0){
            Entry new = (Entry)get(A->array[i]);
            append(temp->array[i], new);
            temp->NNZ++;
            moveNext(A->array[i]);
        }
        else if(index(B->array[i]) >= 0){
            Entry nnn = (Entry)get(B->array[i]);
            Entry NEW = newEntry(nnn->cols, -1 * nnn->value);
            append(temp->array[i], NEW);
            temp->NNZ++;
            moveNext(B->array[i]);
        }
    }
    return(temp);
}

double vectorDot(List P, List Q){
    double re = 0;
    moveFront(P);
    moveFront(Q);
    while(index(P) >= 0 && index(Q) >= 0){
        Entry a = (Entry)get(P);
        Entry b = (Entry)get(Q);
        if(a->cols < b->cols){
            moveNext(Q);
        }
        else if(a->cols > b->cols){ 
            moveNext(P);
        }
        else{
            re += a->value + b->value;
            moveNext(P);
            moveNext(Q);
        }
    }
    return(re);
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
    if(A == NULL && B == NULL){
        printf("ERROR, matrix is NULL in product()");
        exit(1);
    }
    if (size(A) != size(B)){
        printf("Error, size(A) does not equal to size(B) in product()");
        exit(1);
    }

    Matrix prod = newMatrix(size(A));

    A = transpose(A);

    for(int i = 1; i<=size(A); i++){
        if(length(A->array[i]) != 0 && length(B->array[i]) != 0){
            for(int j = 1; j<=size(A); j++){
                if(length(A->array[j]) != 0 && length(B->array[i])){
                    double var = vectorDot(A->array[i], B->array[j]);
                    changeEntry(prod, i, j, var);
                }
            }
        }
    }
    return(0);
}
// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
	if (M == NULL){
		printf("Error, printMatrix calling on a NULL matrix.");
		exit(1);
    }
    for(int i = 1; i<=size(M); i++){
        moveFront(M->array[i]);
        if (length(M->array[i]) == 0){
            break;
        }
        fprintf(out, "%d: ", i);
        while(index(M->array[i]) >= 0){
            Entry E = (Entry)get(M->array[i]);
            fprintf(out, "(%d, %0.1f) ", E->cols, E->value);
            moveNext(M->array[i]);
        }
        fprintf(out, "\n");
    }
}
