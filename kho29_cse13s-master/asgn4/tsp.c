//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "path.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define KB 1024

void print_helper(void) {
    printf("SYNOPSIS\n");
    printf("  Traveling Salesman Problem using DFS.\n");
    printf("\n");
    printf("USAGE\n");
    printf("   ./tsp [-u] [-v] [-h] [-i infile] [-o outfile] \n");
    printf("\n");
    printf("OPTIONS\n");
    printf("   -u             Use undirected graph.\n");
    printf("   -v             Enable verbose printing.\n");
    printf("   -h             Program usage and help.\n");
    printf("   -i infile      Input containing graph (default: stdin)\n");
    printf("   -o outfile     Output of computed graph (default: stdout)\n");
}

void DFS(
    Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile, bool verbose) {
    if (path_length(shortest) == 0 || path_length(curr) < path_length(shortest)) {
        if (path_vertices(curr) + 1 == graph_vertices(G) && graph_has_edge(G, v, START_VERTEX)) {
            path_push_vertex(curr, START_VERTEX, G);
            path_copy(shortest, curr);
        } else {
            for (uint32_t i = 0; i < graph_vertices(G); i++) {
                if (graph_has_edge(G, v, i) == true && graph_visited(G, i) == false) {
                    path_push_vertex(curr, i, G);
                    graph_mark_visited(G, i);
                    DFS(G, i, curr, shortest, cities, outfile, verbose); //bites and outfile);
                    graph_mark_unvisited(G, i);
                    path_pop_vertex(curr, &i, G);
                }
            }
        }
    }
}

int main(int argc, char **argv) {
    FILE *infile = stdin;
    FILE *outfile = stdout;
    bool undirected = false;
    bool verbose = false;
    char buf[KB];
    int i, j, k; //edges to add
    char *cities[KB]; //array to hold cities

    int opt = 0;
    while ((opt = getopt(argc, argv, "hvui:o:")) != -1) {
        switch (opt) {
        case 'h': {
            print_helper();
            break;
        }
        case 'v': {
            verbose = true;
            break;
        }
        case 'u': {
            undirected = true;
            break;
        }
        case 'i': {
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                return false;
            }
            break;
        }
        case 'o': {
            outfile = fopen(optarg, "w");
            break;
        }
        }
    }

    fgets(buf, KB, infile); //read first line from file
    int num_place = atoi(buf); //number of locations
    if (num_place > VERTICES) { //if number of vertices larger than 26, failed
        fclose(infile);
        return false;
    }
    Graph *g = graph_create((uint32_t) buf, undirected);
    //loop to get locations
    for (int b = 0; b < num_place; b++) {
        fgets(buf, KB, infile);
        cities[b] = strdup(buf); //dupe location into cities array
    }
    //Read file till EOF, add edges to graph
    while (fgets(buf, KB, infile) != NULL) {
        fscanf(infile, "%d %d %d", &i, &j, &k);
        graph_add_edge(g, i, j, k);
    }
    //creating current and shortest path
    Path *curr = path_create();
    Path *shortest = path_create();

    //calling DFS
    DFS(g, num_place, curr, shortest, &cities[KB], outfile, verbose);

    //print path
    path_print(shortest, outfile, cities);

    fputs(buf, outfile);
    free(cities);
    graph_delete(&g);
    path_delete(&curr);
    path_delete(&shortest);
    fclose(infile);
    fclose(outfile);

    return 0;
}
