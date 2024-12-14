#include<stdio.h>
#include<stdbool.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "Graph.h"

typedef struct GraphObj {
    int order;
    int size;
    List* neighbors;
    int* parent;
    int* discover;
    int* finished;
    int* colors;
    int time;
} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    assert(G != NULL);

    //# of vertices
    G->order = n;
    //# of edges
    G->size = 0;
    G->time = 0;

    //allocating memory for arrays
    G->neighbors = calloc(n+1, sizeof(List*));
    G->parent = calloc(n+1, sizeof(int*));
    G->discover = calloc(n+1, sizeof(int*));
    G->finished = calloc(n+1, sizeof(int*));
    G->colors = calloc(n+1,sizeof(int*));

    //setting inital values
    for(int i = 1; i <= n; i++) {
        G->neighbors[i] = newList();
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finished[i] = UNDEF;
        G->colors[i] = 'w';
    }
    return(G);
}

void freeGraph(Graph* pG) {
	if(*pG != NULL && pG != NULL) {
        makeNull(*pG);
		free((*pG)->discover);
        free((*pG)->finished);
 		free((*pG)->parent);
 		free((*pG)->colors);
        free((*pG)->neighbors);
	}
	free(*pG);
	*pG = NULL;
}

/*** Access functions ***/
//getting the number of vertices
int getOrder(Graph G) {
    if (G == NULL) {
        printf("Error, Graph is NULL, in getOrder\n");
        exit(1);
    }
    return(G->order);
}

//getSize() returns the number of edegs in the graph
int getSize(Graph G) {
    if (G == NULL) {
        printf("Error, Graph is NULL, in getSize\n");
        exit(1);
    }
    return(G->size);
}

//Function getParent() will return the parent of vertex u in the BFS tree
//created by BFS(), or NIL if BFS() has not yet been called
int getParent(Graph G, int u) {
    if (G == NULL) {
        printf("Error, Graph is NULL\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Error, Vertex is out of bounds in getPartent\n");
        exit(1);
    }
    return G->parent[u];
}

/* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u) {
    if (G == NULL) {
        printf("Error, Graph is NULL\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)){
        printf("Error, Vertex is out of bounds in getDiscover\n");
        exit(1);        
    }
    return(G->discover[u]);
}

/* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u){
    if (G == NULL) {
        printf("Error, Graph is NULL\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)){
        printf("Error, Vertex is out of bounds in getFinish\n");
        exit(1);        
    }
    return(G->finished[u]);
}

/*** Manipulation procedures ***/
void makeNull(Graph G){
    for (int i = 1; i <= getOrder(G); i++){
        G->colors[i] = 'w';
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finished[i] = UNDEF;
        freeList(&(G)->neighbors[i]);
    }
    G->size = 0;
}

//Adds u to v's adjacency list
//and vise versa
//Precondition: 
//two int arguments must between 1 to #vertices
void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
        printf("Error, Graph is NULL\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)){
        printf("Error, Vertex is out of bounds\n");
        exit(1);
    }
    if (v < 1 || v > getOrder(G)) {
        printf("Error, Vertex is out of bounds\n");
        exit(1);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}

//Function adds v to u's adjacentcy list
//same precondition as addEdge()
void addArc(Graph G, int u, int v){
    if (G == NULL) {
        printf("Error, Graph is NULL\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)){
        printf("Error, Vertex is out of bounds\n");
        exit(1);
    }
    if (v < 1 || v > getOrder(G)) {
        printf("Error, Vertex is out of bounds\n");
        exit(1);
    }
    if (length(G->neighbors[u]) == 0){
        append(G->neighbors[u], v);
    }
    else {
        //mimicing insertion sort
        int num = length(G->neighbors[u])-1;
	    moveFront(G->neighbors[u]);
	    while(num > 0 && get(G->neighbors[u]) < v) {
            if(get(G->neighbors[u]) == v){
                return;
            }
		    moveNext(G->neighbors[u]);
		    num--;
	    }
	    if( get(G->neighbors[u]) > v) {
            if(get(G->neighbors[u]) == v){
                return;
            }
 	        insertBefore(G->neighbors[u],v);
 	    }
 	    else {
            if(get(G->neighbors[u]) == v){
                return;
            }
 	        insertAfter(G->neighbors[u],v);
 	    }
    }
    G->size++;
}

//Went to tutor to fix up code
//Based off pseudo code provided from prof tantalo
void visit(Graph G, List L, int x){
    G->discover[x] = ++(G->time);
    G->colors[x] = 'g';
    moveFront(G->neighbors[x]);
    for(int i = 1; i <= length(G->neighbors[x]); i++){
        int y = get(G->neighbors[x]);
        if (G->colors[y] == 'w'){
            G->colors[y] = 'g';
            G->parent[y] = x;
            visit(G, L, y);
        }
        moveNext(G->neighbors[x]);
    }
    G->colors[x] = 'b';
    G->finished[x] = ++(G->time);
    prepend(L, x);
}

/* Pre: length(S)==getOrder(G) */
void DFS(Graph G, List S){
    if (G == NULL){
        printf("Error Graph is NULL. Graph Error, DFS\n");
        exit(1);
    }
    if(S == NULL){
        printf("Error List S is NULL. Graph Error, DFS\n");
        exit(1);
    }
    if (length(S) != getOrder(G)){
        printf("Error, length(s) != getOrder(G). Graph Error, DFS\n");
        exit(1);
    }
    moveFront(S);
    for(int i = 1; i <= length(S); i++){
        int j = get(S);
        G->colors[j] = 'w';
        G->parent[j] = NIL;
        G->finished[j] = UNDEF;
        G->discover[j] = UNDEF;
        moveNext(S);
    }
    G->time = 0;
    moveFront(S);
    for(int x = 1; x <= getOrder(G); x++){
        int k = get(S);
        if(G->colors[k] == 'w'){
            visit(G, S, k);
        }
        moveNext(S);
    }
    for(int j = 1; j <= getOrder(G); j++){
        deleteBack(S);
    }
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G){
	for(int i=1; i<= getOrder(G) ; i++) {
		fprintf(out, "%d", i);
		fprintf(out, "%s", ": ");
		printList(out, G->neighbors[i]);
        fprintf(out, "\n");
	}
}       

//Transpose
//make new graph
//LOOP through all vertices (x)
//  loop through all x's adjacency list (i)
//      for each i, add x into i's adjacency list
Graph transpose(Graph G){
    int num = getOrder(G);
    Graph N = newGraph(num);
    for(int current = 1; current <= getOrder(G); current++){
        moveFront(G->neighbors[current]);
        while(index(G->neighbors[current]) >= 0){
            int num = get(G->neighbors[current]);
            addArc(N, num, current);
            moveNext(G->neighbors[current]);
        }
    }
    return N;
}

Graph copyGraph(Graph G){
    int num = getOrder(G);
    Graph N = newGraph(num);
    for(int i = 1; i < getOrder(G); i++){
        moveFront(G->neighbors[i]);
        if(G->neighbors[i] != NULL){
            N->colors[i] = G->colors[i];
            N->discover[i] = G->discover[i];
            N->finished[i] = G->finished[i];
            N->parent[i] = G->parent[i];
            N->size = G->size;
            N->order = G->order;
            N->neighbors[i] = copyList(G->neighbors[i]);
            moveNext(G->neighbors[i]);
        }
        else {
            moveNext(G->neighbors[i]);
        }
    }
    return(N);
}
