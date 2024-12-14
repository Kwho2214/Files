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
    int source;
    List* neighbors;
    char* colors;
    int* parent;
    int* distance;
} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    assert(G != NULL);

    //# of vertices
    G->order = n;
    //# of edges
    G->size = 0;
    //last used vertex
    G->source = NIL;

    //allocating memory for arrays
    G->neighbors = calloc(n+1, sizeof(List*));
    G->colors = calloc(n+1, sizeof(char*));
    G->parent = calloc(n+1, sizeof(int*));
    G->distance = calloc(n+1, sizeof(int*));

    //setting inital values
    for(int i = 1; i <= n; i++) {
        G->neighbors[i] = newList();
        G->colors[i] = 'w';
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    return(G);
}

void freeGraph(Graph* pG) {
	if(*pG != NULL && pG != NULL) {
        makeNull(*pG);
		free((*pG)->distance);
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
        printf("Error, Graph is NULL\n");
        exit(1);
    }
    return(G->order);
}

//getSize() returns the number of edegs in the graph
int getSize(Graph G) {
    if (G == NULL) {
        printf("Error, Graph is NULL\n");
        exit(1);
    }
    return(G->size);
}

//getSource() returns last vertex used
int getSource(Graph G) {
    if (G == NULL) {
        printf("Error, Graph is NULL\n");
        exit(1);
    }
    return(G->source);
}

//Function getParent() will return the parent of vertex u in the BFS tree
//created by BFS(), or NIL if BFS() has not yet been called
int getParent(Graph G, int u) {
    if (G == NULL) {
        printf("Error, Graph is NULL\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Error, Vertex is out of bounds\n");
        exit(1);
    }
    return G->parent[u];
}

int getDist(Graph G, int u) {
    if (G == NULL) {
        printf("Error, Graph is NULL\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Error, Vertex is out of bounds\n");
        exit(1);
    }
    return G->distance[u];
}

//Function getPath() appends to the List L the vertices of a shortest path in G 
//from source to u, or appends to L the value NIL if
//no such path exists. getPath() has the precondition 
//getSource(G)!=NIL, so BFS() must be called
//before getPath() is called
void getPath(List L, Graph G, int u) {
    if (G == NULL) {
        printf("Error, Graph is NULL\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Error, Vertex is out of bounds\n");
        exit(1);
    }
    
    if (G->source == u) {
        append(L, u);
    }
    else if (G->parent[u] == NIL){
        append(L, NIL);
    }
    else {
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
}

/*** Manipulation procedures ***/
void makeNull(Graph G){
    for (int i = 1; i <= getOrder(G); i++){
        G->colors[i] = 'w';
        G->parent[i] = NIL;
        G->distance[i] = INF;
        freeList(&(G)->neighbors[i]);
    }
    G->source = NIL;
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
		    moveNext(G->neighbors[u]);
		    num--;
	    }
	    if( get(G->neighbors[u]) > v) {
 	        insertBefore(G->neighbors[u],v);
 	    }
 	    else {
 	        insertAfter(G->neighbors[u],v);
 	    }
    }
    G->size++;
}

//BFS algorithm for Graph
//Based off pseudo code provided
//in class examples
void BFS(Graph G, int s) {
    for (int i = 1; i <= getOrder(G); i++) {
        G->colors[i] = 'w';
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->colors[s] = 'g';
    G->distance[s] = 0;
    G->parent[s] = NIL;
    G->source = s;
    List L = newList();
    append(L, s);

    while(length(L) != 0) {
        moveFront(L);
        int x = get(L);
        delete(L);
        moveFront(G->neighbors[x]);
        
        for (int j = 1; j <= length(G->neighbors[x]); j++){
            int y = get(G->neighbors[x]);
            if (G->colors[y] == 'w'){
                G->colors[y] = 'g';
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                append(L, y);
            }
            moveNext(G->neighbors[x]);
        }
        G->colors[x] = 'b';
    }
    freeList(&L);
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