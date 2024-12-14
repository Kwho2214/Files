//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "ht.h"
#include "bst.h"
#include "speck.h"
#include "salts.h"
#include "node.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t lookups;

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    Node **trees;
};

HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        ht->salt[0] = SALT_HASHTABLE_LO;
        ht->salt[1] = SALT_HASHTABLE_HI;
        ht->size = size;
        ht->trees = (Node **) calloc(size, sizeof(Node *));
    }
    return ht;
}

void ht_delete(HashTable **ht) {
    for (uint32_t i = 0; i < (*ht)->size; i++) {
        if ((*ht)->trees[i] != NULL) {
            bst_delete(&(*ht)->trees[i]);
        }
    }
    free((*ht)->trees);
    free((*ht));
    *ht = NULL;
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    lookups += 1;
    uint32_t ind = hash(ht->salt, oldspeak) % ht->size;
    return bst_find(ht->trees[ind], oldspeak);
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    lookups += 1;
    uint32_t ind = hash(ht->salt, oldspeak) % ht->size;
    ht->trees[ind] = bst_insert(ht->trees[ind], oldspeak, newspeak);
}

uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i += 1) {
        if (ht->trees[i] != NULL) {
            count += 1;
        }
    }
    return count;
}

double ht_avg_bst_size(HashTable *ht) {
    double avg_size = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        avg_size += bst_size(ht->trees[i]);
    }
    return avg_size / ht_count(ht);
}

double ht_avg_bst_height(HashTable *ht) {
    double ht_height = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        ht_height += bst_height(ht->trees[i]);
    }
    return ht_height / ht_count(ht);
}

void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht_size(ht); i++) {
        bst_print(ht->trees[i]);
    }
}
