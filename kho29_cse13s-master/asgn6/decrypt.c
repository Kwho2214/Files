//Kwanchak Jason ho
//Cse13s Fall 2021

#include "rsa.h"
#include "randstate.h"
#include "numtheory.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <gmp.h>

#define options "i:o:n:vh"

void help() {
    printf("SYNOPSIS\n");
    printf("   Decrypts data using RSA decryption.\n");
    printf("   Encrypted data is encrypted by the encrypt program.\n");
    printf("\n");
    printf("USAGE\n");
    printf("   ./decrypt [-hv] [-i infile] [-o outfile] -n privkey\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("   -h              Display program help and usage.\n");
    printf("   -v              Display verbose program output.\n");
    printf("   -i infile       Input file of data to decrypt (default: stdin).\n");
    printf("   -o outfile      Output file for decrypted data (default: stdout).\n");
    printf("   -n pvfile       Private key file (default: rsa.priv).\n");
}

int main(int argc, char **argv) {
    int opt = 0;
    bool verbose = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    char *priv = "rsa.priv";
    while ((opt = getopt(argc, argv, options)) != -1) {
        switch (opt) {
        case 'i': {
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                infile = stdin;
            }
            break;
        }
        case 'o': {
            outfile = fopen(optarg, "w");
            if (outfile == NULL) {
                outfile = stdout;
            }
            break;
        }
        case 'n': {
            priv = optarg;
            break;
        }
        case 'v': {
            verbose = true;
            break;
        }
        case 'h': {
            help();
            exit(0);
        }
        default: {
            help();
            exit(0);
        }
        }
    }
    //open private file
    FILE *priv_file = fopen(priv, "r");
    if (priv_file == NULL) {
        fprintf(stderr, "Could not open file.\n");
        exit(1);
    }
    //init mpzs to use
    mpz_t n, d;
    mpz_inits(n, d, NULL);
    rsa_read_priv(n, d, priv_file);
    //printing stats
    if (verbose == true) {
        gmp_printf("%Zd\n", n);
        gmp_printf("%Zd\n", d);
    }
    rsa_decrypt_file(infile, outfile, n, d);
    //Closes and clears files and mpzs
    fclose(infile);
    fclose(outfile);
    fclose(priv_file);
    mpz_clears(n, d, NULL);
}
