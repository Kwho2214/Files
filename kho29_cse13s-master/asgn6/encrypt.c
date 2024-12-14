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
    printf("   Encrypts data using rsa encrytion.\n");
    printf("\n");
    printf("USAGE\n");
    printf("   ./decrypt [-hv] [-i infile] [-o outfile] -n pubkey\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("   -h              Display program help and usage.\n");
    printf("   -v              Display verbose program output.\n");
    printf("   -i infile       Input file of data to encrypt (default: stdin).\n");
    printf("   -o outfile      Output file for encrypted data (default: stdout).\n");
    printf("   -n pubfile       Private key file (default: rsa.pub).\n");
}

int main(int argc, char **argv) {
    int opt = 0;
    bool verbose = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    char *pub = "rsa.pub";
    char user[255] = { 0 };
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
            pub = optarg;
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
    //Open public key file
    FILE *pub_file = fopen(pub, "r");
    if (pub_file == NULL) {
        fprintf(stderr, "Failed to open public file.\n");
    }
    //reading the public key
    mpz_t n, e, s, temp;
    mpz_inits(n, e, s, temp, NULL);
    rsa_read_pub(n, e, s, user, pub_file);
    //printing stats
    if (verbose == true) {
        fprintf(stderr, "%s\n", user);
        gmp_fprintf(stderr, "S: %Zd\n", s);
        gmp_fprintf(stderr, "P: %Zd\n", n);
        gmp_fprintf(stderr, "E: %Zd\n", e);
    }
    mpz_set_str(temp, user, 62);
    if (rsa_verify(temp, s, e, n) == false) {
        printf("Failed to verify.\n");
        exit(1);
    }
    //encrypt file
    rsa_encrypt_file(infile, outfile, n, e);
    //clearing mzps and closing files
    mpz_clears(n, e, s, temp, NULL);
    fclose(infile);
    fclose(outfile);
    fclose(pub_file);
}
