#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "List.h"

//Structs
typedef struct NodeObj* Node;

typedef struct NodeObj {
	void* data;
	Node next;
	Node prev;
} NodeObj;

typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int index;
	int length;
} ListObj;

//Constructors and Destrcutors
//Node constructor
Node newNode(void* data){
	Node N = malloc(sizeof(NodeObj));
	assert(N != NULL);
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}
//Node destructor
void freeNode(Node *pn) {
	if (pn != NULL && *pn != NULL) {
		free(*pn);
		*pn = NULL;
	}
}
//List construct
List newList(void) {
	List L = malloc(sizeof(ListObj));
	assert(L != NULL);
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return(L);				
}

//List Destructor
void freeList(List *pL) {
	if (pL != NULL && *pL != NULL) {
		clear(*pL);
	}
	free(*pL);
	*pL = NULL;
}

//Access functions
int length(List L) {
	if (L == NULL){
		printf("Error, access function length(List L)");
		exit(1);
	}
	return(L->length);
}

int index(List L) {
	if (L == NULL){
		printf("Error, access function index(List L)");
		exit(1);
	}
	return(L->index);
}

void* front(List L){
	if (L == NULL){
		printf("Error, access function front(List L)");
		exit(1);
	}
	else {
		if (length(L) > 0) {
			return(L->front->data);
		}
		else {
			printf("Error, called front on empty list.");
			exit(1);
		}
	}
}

void* back(List L){
	if (L == NULL){
		printf("Error, access function get(List L)");
		exit(1);
	}
	return(L->back->data);
}

void* get(List L){
	if (L == NULL){
		printf("Error, access function get(List L)");
		exit(1);
	}
	//printf("length %d index %d cursor: %d\n", length(L), index(L), L->cursor->data);
	if(length(L) > 0 && L->cursor != NULL) {
			
			return(L->cursor->data);
	}
	else {
		printf("List Error: calling get() on empty List or cursor is undefined\n");
		exit(1);
	}
}

// Manipulation procedures ----------------------------------------------------
void clear(List L){
	if (L == NULL){
		printf("Error, clear function, manupulator procedures.");
		exit(1);
	}
	if(length(L) > 0) {
		while(length(L) > 0 && L != NULL) {
			deleteFront(L);
		}
	}
}

// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, void* x) {
	if (L == NULL){
		printf("Error, set function failed.");
		exit(1);
	}
	if (length(L) > 0 && index(L) >= 0) {
		L->cursor->data = x;
	}
	else {
		printf("Error, set function failed.");
		exit(1);
	}
}

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L) {
	if (L == NULL) {
		printf("Error, moveFront on NULL List.");
		exit(1);
	}
	if (length(L) > 0) {
		L->cursor = L->front;
		L->index = 0;
	}
}

// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L) {
	if (L == NULL) {
		printf("Error, moveBack on NULL List");
		exit(1);
	}
	if (length(L) > 0) {
		L->cursor = L->back;
		L->index = length(L) - 1;
	}
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L) {
	if (L == NULL){
		printf("Error, movePrev on NULL List");
		exit(1);
	}
	if (L->cursor != NULL && L->cursor != L->front){
		L->cursor = L->cursor->prev;
		L->index -= 1;
	}
	else if(L->cursor == L->front) {
		L->cursor = NULL;
		L->index = -1;
	}
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
	if (L == NULL){
		printf("Error, moveBack on NULL List");
		exit(1);
	}
	if (L->cursor != NULL && L->cursor != L->back){
		L->cursor = L->cursor->next;
		L->index += 1;
	}
	else if (L->cursor == L->back){
		L->cursor = NULL;
		L->index = -1;
	}
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, void* x) {
	Node N = newNode(x); 
	if (L == NULL){
		printf("Error, prepend onto a NULL List.");
		exit(1);
	}
	if (length(L) == 0){
		L->front = N;
		L->back = N;
		L->length += 1;
		L->index = 1;
		L->cursor = L->front;
	}
	else{
		N->next = L->front;
		N->prev = NULL;
		L->front->prev = N;
		L->front = N;
		L->length += 1;
		L->index += 1;
	}
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, void* x) {
	Node N = newNode(x); 
	if (L == NULL){
		printf("Error, append onto a NULL List.");
		exit(1);
	}
	if (length(L) == 0){
		L->front = N;
		L->back = N;
		L->length += 1;
		L->cursor = L->back;
	}
	else {
		N->prev = L->back;
		L->back->next = N;		
		L->back = N;
		N->next = NULL;
		L->length += 1;
	}
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, void* x) {
	if (L == NULL){
		printf("Error, insertBefore onto a NULL List.");
		exit(1);
	}
	if (L->cursor == L->front) {
		Node N = newNode(&x);
		N->prev = NULL;
		L->front->prev = N;
		N->next = L->front;
		L->front = N;
		L->length += 1;
		L->index += 1;
	}
	else if (length(L) > 0 && index(L) >= 0) {
		Node N = newNode(x);
		N->prev = L->cursor->prev;
		L->cursor->prev->next = N;
		L->cursor->prev = N;
		N->next = L->cursor;
		L->length += 1;
		L->index += 1;
	}
	else {
		printf("Error, calling intsertBefore onto an empty list.");
		exit(1);
	}
}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, void* x) {
	if (L == NULL){
		printf("Error, insertAfter onto a NULL List.");
		exit(1);
	}
	if (L->cursor == L->back) {
		Node N = newNode(&x);
		N->next = NULL;
		L->cursor->next = N;
		N->prev = L->cursor;
		L->back = N;
		L->length += 1;
		}
	else if (length(L) > 0 && index(L) >= 0) {
		Node N = newNode(x);
		N->next = L->cursor->next;
		L->cursor->next = N;
		N->prev = L->cursor;
		L->length += 1;
	}
	else {
		printf("Error, calling intsertAfter onto an empty list.");
		exit(1);
	}
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) {
	Node N = NULL;
	N = L->front;
	if (L == NULL){
		printf("Error, insertAfter onto a NULL List.");
		exit(1);
	}
	if (index(L) == 0){
		L->cursor = NULL;
		L->index = -1;
	}
	if (length(L) > 1){
		L->front = L->front->next;
		L->front->prev = NULL;
		L->length -= 1;
		if (L->cursor != NULL) {
			L->index -= 1;
		}
		freeNode(&N);
		//check if cursor is at front
	}
	else {
		L->back = L->front = NULL;
		L->length -= 1;
		freeNode(&N);
	}
}

// Delete the back element. Pre: length()>0
void deleteBack(List L) {
	Node N = NULL;
	N = L->back;
	if (L == NULL){
		printf("Error, insertAfter onto a NULL List.");
		exit(1);
	}
	if(length(L) <= 0) {
		printf("Error, list length is less than equal to 0");
		exit(1);
	}
	if (length(L) > 1) {
		L->back = L->back->prev;
		L->back->next = NULL;
		L->length -= 1;
		freeNode(&N);
		//checking if cursor = back
		if (index(L) == length(L)){
			L->cursor = NULL;
			L->index = -1;
		}
	}
	else if (length(L) == 1) {
		L->back = NULL;
		L->length -= 1;
		freeNode(&N);
	}
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
	if (L == NULL){
		printf("Error, calling delete onto a NULL List.");
		exit(1);
	}
	if (length(L) > 0 && index(L) >= 0){
		if (length(L) == 1){
			clear(L);
		}
		else if (L->cursor->prev != NULL && L->cursor->next != NULL){
			Node N = L->cursor;
			Node D = L->cursor->prev;
			D->next = L->cursor->next;
			freeNode(&N);
			L->cursor = NULL;
			L->length -= 1;
			L->index = -1;
		}
		else if (L->cursor == L->front){
			deleteFront(L);
		}
		else if (L->cursor == L->back){
			deleteBack(L);
		}
	}
}


