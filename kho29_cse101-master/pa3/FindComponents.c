#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){
	FILE *in, *out;
	char line[MAX_LEN];
	int n = 0;

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
	fscanf(in, "%d", &n);
	Graph G = newGraph(n);
	
	//making our graph
	while(fgets(line, MAX_LEN, in) != NULL){
		int u, v = 0;
		fscanf(in, "%d %d", &u, &v);
		if (u == 0 && v == 0) {
			break;
		}
		addArc(G,u,v);
	}
    
    fprintf(out, "%s\n", "Adjacency list representation of G:");
	printGraph(out, G);

	List L = newList();
	for(int i = 1; i <= n; i++){
		append(L, i);
	}

	DFS(G, L);
	Graph trans = NULL;
	trans = transpose(G);
	DFS(trans, L);

	//How many Strongly connect comps
	int count = 0;
	moveFront(L);
	for(int i = 1; i<= length(L); i++){
		int num_par = getParent(trans, get(L));
		if(num_par == 0){
			count++;
		}
		moveNext(L);
	}
	fprintf(out, "%s","\n");
	fprintf(out, "G contains %d strongly connected components:\n", count);

	//Finding the comps
	List temp = newList();
	moveBack(L);
	int num = 1;
	for(int i = 1; i<= length(L); i++){
		int x = getParent(trans, get(L));
		//Strongly connected components
		if(x == 0){
			prepend(temp, get(L));
			fprintf(out, "Component %d: ", num);
			printList(out, temp);
			fprintf(out, "\n");
			clear(temp);
			num++;
		}
		else {
			prepend(temp, get(L));
		}
		movePrev(L);
	}

	//free memory
	fclose(in);
	fclose(out);
	freeList(&temp);
	freeList(&L);
	freeGraph(&G);
	freeGraph(&trans);
}