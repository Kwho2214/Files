//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "bf.h"
#include "ht.h"
#include "bst.h"
#include "parser.h"
#include "messages.h"
#include <stdio.h>
#include <stdbool.h>
#include <regex.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define size_of_ht   65536
#define size_of_bf   1048576
#define KB           1024
#define word_pattern "[a-zA-Z0-9_]+(('|-)[a-zA-Z0-9_]+)*"

void help() {
    printf("SYNOPSIS\n");
    printf("  A word filtering program for the GPRSC.\n");
    printf("  Filters out and reports bad words parsed from stdin.\n");
    printf("\n");
    printf("USAGE\n");
    printf("  ./banhammer [-hs] [-t size] [-f size]\n");
    printf("n");
    printf("OPTIONS\n");
    printf("  -h           Program usage and help.\n");
    printf("  -s           Print program statistics.\n");
    printf("  -t size      Specify hash table size (default: 2^16).\n");
    printf("  -f size      Specify Bloom filter size (default: 2^20).\n");
}

int main(int argc, char **argv) {
    FILE *bad = fopen("badspeak.txt", "r");
    FILE *new = fopen("newspeak.txt", "r");
    char badspeak[KB];
    char oldspeak[KB];
    char newspeak[KB];
    bool verbose = false;
    uint32_t ht_sizes = size_of_ht;
    uint32_t bf_sizes = size_of_bf;
    int opt = 0;
    while ((opt = getopt(argc, argv, "ht:f:s")) != -1) {
        switch (opt) {
        case 'h': {
            help();
            exit(0);
        }
        case 't': {
            ht_sizes = atoi(optarg);
            break;
        }
        case 'f': {
            bf_sizes = atoi(optarg);
            break;
        }
        case 's': {
            verbose = true;
            break;
        }
        default: {
            help();
            exit(0);
        }
        }
    }
    //create bloomfilter and hashtable
    HashTable *ht = ht_create(ht_sizes);
    BloomFilter *bf = bf_create(bf_sizes);
    //scan in badspeak words
    while (fscanf(bad, "%s", badspeak) != EOF) {
        bf_insert(bf, badspeak);
        ht_insert(ht, badspeak, NULL);
    }
    //read in oldspeak and newspeak words
    while (fscanf(new, "%s %s", oldspeak, newspeak) != EOF) {
        bf_insert(bf, oldspeak);
        ht_insert(ht, oldspeak, newspeak);
    }
    //closing opened files
    fclose(bad);
    fclose(new);
    //Regex
    //Based of example from Asgn7 PDF
    char *word = NULL;
    regex_t re;
    if (regcomp(&re, word_pattern, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }
    //make binary search tree to hold words
    Node *badspeak_tree = bst_create();
    Node *mixspeak_tree = bst_create();

    while ((word = next_word(stdin, &re)) != NULL) {
        //making to lowercase, got algorithm on stack overflow
        char *point = word;
        while (*point) {
            *point = tolower(*point);
            point++;
        }
        //if the word is in the bloom filter
        if (bf_probe(bf, word) == true) {
            //if the word is in hashtable and has newspeak translation
            if (ht_lookup(ht, word) && ht_lookup(ht, word)->newspeak) {
                //insert into mixspeak
                mixspeak_tree = bst_insert(
                    mixspeak_tree, ht_lookup(ht, word)->oldspeak, ht_lookup(ht, word)->newspeak);
                //if the word is in hastable but no newspeak translation
            } else if (ht_lookup(ht, word) && ht_lookup(ht, word)->newspeak == NULL) {
                //insert into badspeak
                badspeak_tree = bst_insert(badspeak_tree, ht_lookup(ht, word)->oldspeak, NULL);
            }
        }
    }
    //if verbose, print the stats
    if (verbose == true) {
        printf("Average BST size: %0.6f\n", ht_avg_bst_size(ht));
        printf("Average BST height: %0.6f\n", ht_avg_bst_height(ht));

        double avg_branches = (double) branches / (double) lookups;
        printf("Average Branches traversed: %0.6f\n", avg_branches);

        double ht_load = 100 * (ht_count(ht) / ht_size(ht));
        printf("Hash table load: %.6f", ht_load);
        printf("%%\n");

        double bf_load = 100 * (bf_count(bf) / bf_size(bf));
        printf("Bloom Filter load: %.6f", bf_load);
        printf("%%\n");

    } else {
        if (bst_size(mixspeak_tree) > 0 && bst_size(badspeak_tree) == 0) {
            printf("%s\n", goodspeak_message);
            bst_print(mixspeak_tree);
        } else if (bst_size(mixspeak_tree) > 0 && bst_size(badspeak_tree) > 0) {
            printf("%s\n", mixspeak_message);
            bst_print(badspeak_tree);
            bst_print(mixspeak_tree);
        } else if (bst_size(mixspeak_tree) == 0 && bst_size(badspeak_tree) > 0) {
            printf("%s\n", badspeak_message);
            bst_print(badspeak_tree);
        }
    }
    //free memory
    bst_delete(&badspeak_tree);
    bst_delete(&mixspeak_tree);
    ht_delete(&ht);
    bf_delete(&bf);
    clear_words();
    regfree(&re);
    return 0;
}
