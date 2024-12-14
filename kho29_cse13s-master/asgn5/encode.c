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

extern int *global_read;
extern int *global_wrote;

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
        default: help(); exit(0);
        }
    }
    //Create histogram
    uint64_t histogram[ALPHABET] = { 0 };
    uint32_t uniq_sym = 0;
    uint8_t buff[BLOCK];
    histogram[0]++;
    histogram[ALPHABET - 1]++;
    int x = read_bytes(infile, buff, BLOCK);
    while (x > 0) {
        for (int i = 0; i < x; i++) {
            if (histogram[buff[i]] == 0) {
                uniq_sym += 1;
            }
            histogram[buff[i]]++;
        }
    }
    //build code table
    Node *root = build_tree(histogram);
    Code code_table[ALPHABET] = { 0 };
    build_codes(root, code_table);
    //File permissions
    struct stat buffer;
    fstat(infile, &buffer);
    fchmod(outfile, buffer.st_mode);
    Header h = { 0, 0, 0, 0 };
    h.magic = MAGIC;
    h.permissions = buffer.st_mode;
    h.tree_size = (3 * uniq_sym) - 1;
    h.file_size = buffer.st_size;
    //write to outfile
    write_bytes(outfile, (uint8_t *) &h, sizeof(h));
    dump_tree(outfile, root);
    //writing the codes
    lseek(infile, 0, SEEK_SET);
    int y = read_bytes(infile, buff, BLOCK);
    while (y > 0) {
        for (int i = 0; i < y; i++) {
            write_code(outfile, &code_table[buff[i]]);
        }
    }
    flush_codes(outfile);
    if (verbos == true) {
        printf("Bytes read: %d\n", *global_read);
        printf("Bytes written: %d\n", *global_wrote);
    }
    delete_tree(&root);
    close(outfile);
    close(infile);
}
