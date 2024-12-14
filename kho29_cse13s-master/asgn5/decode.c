//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "pq.h"
#include "node.h"
#include "code.h"
#include "huffman.h"
#include "io.h"
#include "stack.h"
#include "defines.h"
#include "header.h"
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define OPTIONS "hvi:o:"

void help(void) {
    printf("SYNOPSIS\n");
    printf("  A Huffman encoder.\n");
    printf("  Compresses a file using the Huffman coding algorithm.\n");
    printf("\n");
    printf("USAGE\n");
    printf("  ./encode [-h] [-i infile] [-o outfile]\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("  -h             Program usage and help.\n");
    printf("  -v             Print compression statistics.\n");
    printf("  -i infile      Input file to compress.\n");
    printf("  -o outfile     Output of compressed data.\n");
}

int main(int argc, char **argv) {
    int opt = 0;
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
    bool verbos = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': help(); break;
        case 'v': verbos = true; break;
        case 'i':
            infile = open(optarg, O_RDONLY);
            if (infile == -1) {
                fprintf(stderr, "Error, failed to open file.\n");
                return false;
            }
            break;
        case 'o':
            outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);
            if (outfile == -1) {
                fprintf(stderr, "Error, failed to open file.\n");
                return false;
            }
            break;
        }
    }
    //file permissions
    Header h = { 0, 0, 0, 0 };
    read_bytes(infile, (uint8_t *) &h, sizeof(h));
    if (h.magic != MAGIC) {
        fprintf(stderr, "wrong MAGIC number.");
        close(infile);
        close(outfile);
        exit(1);
    }
    fchmod(outfile, h.permissions);
    //reconstruct tree
    uint8_t dumped_tree[h.tree_size];
    uint8_t buffer[BLOCK] = { 0 };
    uint8_t buff[BLOCK];
    uint8_t bit = 0;
    uint64_t size_file = 0;
    Node *next_node = NULL;
    read_bytes(infile, buff, h.tree_size);
    Node *root = rebuild_tree(h.tree_size, &dumped_tree[h.tree_size]);
    while (read_bit(infile, &bit)) {
        if (bit == 0) {
            next_node = root->left;
            size_file += 1;
        } else if (bit == 1) {
            next_node = root->right;
            size_file += 1;
        }
        if (root->left == NULL && root->right == NULL) {
            //write to buffer
            write_bytes(outfile, buffer, sizeof(root->symbol));
            //reset current node to root
            next_node = root;
        }
        //if the file size counter reaches file size from header
        //We done
        if (size_file == h.file_size) {
            break;
        }
    }
    //closes infile and outfile
    close(infile);
    close(outfile);
}
