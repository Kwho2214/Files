//Kwanchak Jason Ho
////Cse13s Fall 2021

#include "bst.h"
#include "node.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//from lecture 18 trees and bst
static uint32_t max(uint32_t x, uint32_t y) {
    return x > y ? x : y;
}

uint64_t branches;

Node *bst_create(void) {
    return NULL;
}

void bst_delete(Node **root) {
    if (*root != NULL) {
        if ((*root)->left != NULL) {
            bst_delete(&(*root)->left);
        }
        if ((*root)->right != NULL) {
            bst_delete(&(*root)->right);
        }
        node_delete(&(*root));
    }
}

uint32_t bst_height(Node *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + max(bst_height(root->left), bst_height(root->right));
}

uint32_t bst_size(Node *root) {
    if (root == NULL) {
        return 0;
    }
    return bst_size(root->left) + bst_size(root->right) + 1;
}
//went to eric's section for find
Node *bst_find(Node *root, char *oldspeak) {
    Node *node = root;
    if (root != NULL && oldspeak != NULL) {
        while (node != NULL && strcmp(node->oldspeak, oldspeak) != 0) {
            branches += 1;
            if (strcmp(node->oldspeak, oldspeak) > 0) {
                node = node->left;
                branches += 1;
            }
            if (strcmp(node->oldspeak, oldspeak) < 0) {
                node = node->right;
                branches += 1;
            }
        }
    }
    return node;
}

Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    if (root == NULL) {
        return node_create(oldspeak, newspeak);
        branches += 1;
    }
    if (strcmp(root->oldspeak, oldspeak) > 0) {
        root->left = bst_insert(root->left, oldspeak, newspeak);
        branches += 1;

    } else if (strcmp(root->oldspeak, oldspeak) < 0) {
        root->right = bst_insert(root->right, oldspeak, newspeak);
        branches += 1;

    } else if (strcmp(root->oldspeak, oldspeak) == 0) {
        return root;
    }
    return root;
}

void bst_print(Node *root) {
    if (root) {
        bst_print(root->left);
        node_print(root);
        bst_print(root->right);
    }
}
