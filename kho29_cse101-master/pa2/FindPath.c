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
	
	while(fgets(line, MAX_LEN, in) != NULL){
		int u, v = 0;
		fscanf(in, "%d %d", &u, &v);
		if (u == 0 && v == 0) {
			break;
		}
		addEdge(G,u,v);
	}
	printGraph(out, G);

	while( fgets(line, MAX_LEN, in) != NULL){
		int u, v = 0;
		fscanf(in, "%d %d", &u, &v);
		if (u == 0 && v == 0) {
			break;
		}
		BFS(G,u);
		fprintf(out,"\n");
		fprintf(out, "The distance from %d to %d is ", u, v);
		int dist = getDist(G,v);

		if (dist == INF){
			fprintf(out, "infinity\n");
			fprintf(out, "No %d-%d path exits\n", u, v);
			fprintf(out,"\n");
		}
		else {
			fprintf(out, "%d\n", dist);
			fprintf(out, "A shortest %d-%d is ", u, v);
			List L = newList();
			getPath(L, G, v);
			printList(out, L);
			fprintf(out,"\n");
			fprintf(out,"\n");
			freeList(&L);
		}
	}

	fclose(in);
	fclose(out);
	freeGraph(&G);
}