//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Path {
    Stack *vertices;
    uint32_t length;
};

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->vertices = stack_create(VERTICES);
    if (!p) {
        return NULL;
    }
    p->length = 0;
    return p;
}

void path_delete(Path **p) {
    stack_delete(&(*p)->vertices);
    free(*p);
    *p = NULL;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    if (p->length == 0) {
        stack_push(p->vertices, v);
        p->length += graph_edge_weight(G, START_VERTEX, v);
        return true;
    } else {
        uint32_t prev;
        stack_peek(p->vertices, &prev);
        stack_push(p->vertices, v);
        if (stack_push(p->vertices, v) == false) {
            return false;
        }
        p->length += graph_edge_weight(G, prev, v);
        return true;
    }
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (p->length == 0) {
        return false;
    }
    if (stack_pop(p->vertices, v) == false) {
        return false;
    }
    stack_pop(p->vertices, v);
    uint32_t prev;
    stack_peek(p->vertices, &prev);
    p->length -= graph_edge_weight(G, prev, *v);
    return true;
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

void path_copy(Path *dst, Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length;
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    stack_print(p->vertices, outfile, cities);
}
