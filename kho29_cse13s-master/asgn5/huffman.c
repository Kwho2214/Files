//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "huffman.h"
#include "code.h"
#include "pq.h"
#include "io.h"
#include "stack.h"
#include "defines.h"
#include "header.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

Node *build_tree(uint64_t hist[static ALPHABET]) {
    //make priority queue to build tree
    PriorityQueue *q = pq_create(ALPHABET);
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i] == 0) {
            Node *n = node_create(i, hist[i]);
            enqueue(q, n);
        }
    }
    while (pq_size(q) > 1) {
        Node *left = NULL;
        Node *right = NULL;
        dequeue(q, &left);
        dequeue(q, &right);
        enqueue(q, node_join(left, right));
    }
    //Gives root of tree back
    Node *root = NULL;
    dequeue(q, &root);
    return root;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    //Initializes a code table
    Code c = { 0, { 0 } };
    if (root != NULL) {
        if ((root->left) == NULL && (root->right) == NULL) {
            table[root->symbol] = c;
        } else { //must be internal node
            code_push_bit(&c, 0); //push 0 and go left
            build_codes(root->left, table);
            code_pop_bit(&c, 0);

            code_push_bit(&c, 1); //push 1 and go right
            build_codes(root->right, table);
            code_pop_bit(&c, 0);
        }
    }
}

void dump_tree(int outfile, Node *root) {
    static uint8_t buffer[BLOCK];
    if (root) {
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);
        if (root->left != NULL && root->right != NULL) { //if not leaf, write symbol and L
            write_bytes(outfile, buffer, sizeof('L'));
            write_bytes(outfile, buffer, sizeof(root->symbol));
        } else {
            write_bytes(outfile, buffer, sizeof('I')); //if internal write and I
        }
    }
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree_dump[static nbytes]) {
    Stack *s = stack_create(ALPHABET); //create stack size ALPHABET
    for (uint16_t i = 0; i < nbytes; i++) {
        if (tree_dump[i] == 'L') {
            Node *n = node_create(tree_dump[i], 0); //make nodes with symbol from table
            stack_push(s, n); //push nodes to stack
            i += 1;
        } else { //internal node
            Node *L = NULL;
            Node *R = NULL;
            stack_pop(s, &R); //pops the right child
            stack_pop(s, &L); //pops the left child
            Node *parent = node_join(L, R); //creates the parent node
            stack_push(s, parent); //pushes parent node back on to stack
        }
    }
    //returns the root of the tree
    Node *root = NULL;
    stack_pop(s, &root);
    stack_delete(&s);
    return root;
}

void delete_tree(Node **root) {
    //uses post order traversal to delete the tree
    if (((*root)->left) != NULL) {
        delete_tree(&(*root)->left);
    }
    if (((*root)->right) != NULL) {
        delete_tree(&(*root)->right);
    }
    node_delete(&(*root));
}
