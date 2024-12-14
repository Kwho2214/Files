//kwanchak Jason Ho
//Cse13s Fall 2021

#include "graph.h"

#include "vertices.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//included inttypes to test adt
#include <inttypes.h>

struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) calloc(1, sizeof(Graph));
    G->vertices = vertices;
    G->undirected = undirected;
    return G;
}

void graph_delete(Graph **G) {
    free(*G);
    *G = NULL;
    return;
}

uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (i >= 0 && i <= G->vertices && j >= 0 && j <= G->vertices) {
        G->matrix[i][j] = k;
        return true;
        if (G->undirected == true) {
            G->matrix[j][i] = k;
            return true;
        }
    } else {
        return false;
    }
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (i >= 0 && i <= G->vertices && j >= 0 && j <= G->vertices) {
        if (G->matrix[i][j] > 0) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (i >= 0 && i <= G->vertices && j >= 0 && j <= G->vertices) {
        if (G->undirected == false) {
            return G->matrix[i][j];
        } else {
            return G->matrix[j][i];
        }
    } else {
        return false;
    }
}

bool graph_visited(Graph *G, uint32_t v) {
    if (v >= 0 && v <= G->vertices) {
        return G->visited[v];
    } else {
        return false;
    }
}

void graph_mark_visited(Graph *G, uint32_t v) {
    if (v >= 0 && v <= G->vertices) {
        G->visited[v] = true;
    }
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v >= 0 && v <= G->vertices) {
        G->visited[v] = false;
    }
}

void graph_print(Graph *G) {
    for (uint32_t i = 0; i < G->vertices; i++) {
        for (uint32_t j = 0; j < G->vertices; j++) {
            printf("%d\t", G->matrix[i][j]);
        }
    }
}
