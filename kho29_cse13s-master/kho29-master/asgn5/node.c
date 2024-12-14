//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "node.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

Node *node_create(uint8_t symbol, uint64_t frequency) {
    //create node allocate memory
    Node *n = (Node *) malloc(sizeof(Node));
    n->left = NULL; //node left is null
    n->right = NULL; //node right is null
    n->symbol = symbol;
    n->frequency = frequency;
    return n;
}

void node_delete(Node **n) {
    free((*n)->left); //free the left node
    free((*n)->right); //free right node
    free(*n); //frees the node
    *n = NULL; //set pointer to null
}

Node *node_join(Node *left, Node *right) {
    //make parent node, allocate memory using node_create
    Node *parent = node_create('$', left->frequency + right->frequency);
    parent->left = left; //parent's left is a child node
    parent->right = right; //parent's right is its child node
    return parent;
}

void node_print(Node *n) {
    //to print node
    printf("symbol: %c, freq: %lu\n", n->symbol, n->frequency);
}
