//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "node.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        if (oldspeak == NULL) {
            n->oldspeak = NULL;
        } else {
            n->oldspeak = strdup(oldspeak);
        }
        if (newspeak == NULL) {
            n->newspeak = NULL;
        } else {
            n->newspeak = strdup(newspeak);
        }
        n->left = NULL;
        n->right = NULL;
    }
    return n;
}

void node_delete(Node **n) {
    free((*n)->oldspeak);
    free((*n)->newspeak);
    free(*n);
    n = NULL;
}

void node_print(Node *n) {
    if (n->oldspeak != NULL && n->newspeak != NULL) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    } else if (n->newspeak == NULL) {
        printf("%s\n", n->oldspeak);
    }
}
