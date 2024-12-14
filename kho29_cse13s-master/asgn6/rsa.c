//Kwanchak Jaosn Ho
//Cse13s Fall 2021

#include "numtheory.h"
#include "randstate.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gmp.h>
#include <time.h>

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    mpz_t p_one, q_one, temp, tot;
    mpz_inits(p_one, q_one, temp, tot, NULL);

    //to get range random() % (upper - lower + 1) + lower
    uint64_t p_bit = (random() % ((2 * nbits / 4))) + (nbits / 4);
    uint64_t q_bit = nbits - p_bit;

    make_prime(p, p_bit, iters);
    make_prime(q, q_bit, iters);
    mpz_mul(n, p, q);

    mpz_sub_ui(p_one, p, 1);
    mpz_sub_ui(q_one, q, 1);
    mpz_mul(tot, p_one, q_one);

    do {
        mpz_urandomb(e, state, nbits);
        gcd(temp, e, tot);
    } while (mpz_cmp_ui(temp, 1) != 0);

    mpz_clears(p_one, q_one, temp, tot, NULL);
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n", n);
    gmp_fprintf(pbfile, "%Zx\n", e);
    gmp_fprintf(pbfile, "%Zx\n", s);
    fprintf(pbfile, "%s\n", username);
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx\n", n);
    gmp_fscanf(pbfile, "%Zx\n", e);
    gmp_fscanf(pbfile, "%Zx\n", s);
    fscanf(pbfile, "%s\n", username);
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t toh, q_one, p_one;
    mpz_inits(toh, q_one, p_one, NULL);

    mpz_sub_ui(q_one, q, 1);
    mpz_sub_ui(p_one, p, 1);
    mpz_mul(toh, p_one, q_one);
    mod_inverse(d, e, toh);
    mpz_clears(toh, p_one, q_one, NULL);
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n", n);
    gmp_fprintf(pvfile, "%Zx\n", d);
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx\n", n);
    gmp_fscanf(pvfile, "%Zx\n", d);
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    mpz_t m, c;
    mpz_inits(m, c, NULL);
    size_t k = mpz_sizeinbase(n, 2) - 1 / 8; //find the size of k
    uint8_t *block = (uint8_t *) calloc(k, sizeof(uint8_t)); //allocate block
    block[0] = 0xff; // set 0th index to oxff
    while (!feof(infile)) { //while file still have things to read
        size_t j = fread(block + 1, sizeof(uint8_t), k - 1, infile); //j = bytes read
        mpz_import(m, j, 1, sizeof(uint8_t), 1, 0, block); //import that to m
        rsa_encrypt(c, m, e, n); //encrypt cyphertext
        gmp_fprintf(outfile, "%Zx\n", c); //print to outfile
    }
    mpz_clears(m, c, NULL);
    free(block);
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n);
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    mpz_t m, c;
    mpz_inits(m, c, NULL);
    size_t k = mpz_sizeinbase(n, 2) - 1 / 8; //log base 2 of n  -1
    uint8_t *block = (uint8_t *) calloc(k, sizeof(uint8_t)); //allocating array with capacity k
    size_t j;
    while (!feof(infile)) { //if read in k bytes stopes
        gmp_fscanf(infile, "%Zx\n", c);
        rsa_decrypt(m, c, d, n);
        mpz_export(block, &j, 1, sizeof(uint8_t), 1, 0, m);
        fwrite(block + 1, sizeof(uint8_t), j - 1, outfile);
    }
    mpz_clears(m, c, NULL);
    free(block);
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t t;
    mpz_inits(t, NULL);
    pow_mod(t, s, e, n);
    if (mpz_cmp(m, t) == 0) {
        return true;
    } else {
        return false;
    }
}
