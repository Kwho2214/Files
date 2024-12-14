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

#define options "b:i:n:d:s:vh"

void help() {
    printf("SYNOPSIS\n");
    printf("   Generates an RSA public/private key pair.\n");
    printf("\n");
    printf("USAGE\n");
    printf("   ./keygen [-hv] [-b bits] [-i iterations of Miller Rabin] -n pbfile -d pvfile\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("   -h              Display program help and usage.\n");
    printf("   -v              Display verbose program output.\n");
    printf("   -b bits         Minimum bits needed for public key n (default: 256).\n");
    printf("   -i confidence   Miller-Rabin iterations for testing primes (default: 50)\n");
    printf("   -n pbfile       Public key file (default: rsa.pub).\n");
    printf("   -d pvfile       Private key file (default: rsa.priv).\n");
    printf("   -s seed         Random seed for testing.\n");
}

int main(int argc, char **argv) {
    int opt = 0;
    uint64_t nbits = 256;
    uint64_t iters = 50;
    char *priv_name = "rsa.priv";
    char *pub_name = "rsa.pub";
    uint64_t seed = time(NULL);
    char *username;
    bool verbose = false;
    while ((opt = getopt(argc, argv, options)) != -1) {
        switch (opt) {
        case 'b': {
            nbits = atoi(optarg);
            break;
        }
        case 'i': {
            iters = atoi(optarg);
            break;
        }
        case 'n': {
            pub_name = optarg;
            break;
        }
        case 'd': {
            priv_name = optarg;
            break;
        }
        case 's': {
            seed = atoi(optarg);
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
    //Open file
    FILE *priv = fopen(priv_name, "w");
    if (priv == NULL) {
        fprintf(stderr, "Error, unable to open file.\n");
        exit(1);
    }
    FILE *pub = fopen(pub_name, "w");
    if (pub == NULL) {
        fprintf(stderr, "Unable to open file.\n");
        exit(1);
    }
    //To give file permissions
    fchmod(fileno(priv), (mode_t) 0600);
    //making public and private key
    randstate_init(seed);
    mpz_t p, q, n, e, d;
    mpz_inits(p, q, n, e, d, NULL);
    rsa_make_pub(p, q, n, e, nbits, iters);
    rsa_make_priv(d, e, p, q);
    //getting username
    username = getenv("USER");
    mpz_t s, m;
    mpz_inits(s, m, NULL);
    mpz_set_str(m, username, 62);

    rsa_sign(s, m, d, n);
    rsa_write_pub(n, e, s, username, pub);
    rsa_write_priv(n, d, priv);
    if (verbose == true) {
        printf("Username: %s\n", username);
        gmp_printf("s: %Zd\n", s);
        gmp_printf("p: %Zd\n", p);
        gmp_printf("q: %Zd\n", q);
        gmp_printf("n: %Zd\n", n);
        gmp_printf("e: %Zd\n", e);
        gmp_printf("d: %Zd\n", d);
    }
    mpz_clears(p, q, n, e, d, s, m, NULL);
    fclose(pub);
    fclose(priv);
    randstate_clear();
}
