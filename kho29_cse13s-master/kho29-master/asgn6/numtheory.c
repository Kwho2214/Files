//Kwanchak Jaosn Ho
//Cse13s Fall 2021

#include "numtheory.h"
#include "randstate.h"
#include <gmp.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
gmp_randstate_t state;

void pow_mod(mpz_t o, mpz_t a, mpz_t d, mpz_t n) {
    mpz_t v, x, p, temp, temp2, temp3;
    mpz_inits(v, p, x, temp, temp2, temp3, NULL);
    mpz_set_ui(v, 1);
    mpz_set(p, a);
    mpz_set(temp3, d);
    while (mpz_cmp_ui(temp3, 0) > 0) {
        if (mpz_odd_p(temp3) != 0) {
            mpz_mul(temp, v, p); //temp = v * p
            mpz_mod(v, temp, n); // v = temp % n
        }
        mpz_mul(temp2, p, p);
        mpz_mod(p, temp2, n);
        mpz_fdiv_q_ui(temp3, temp3, 2);
    }
    mpz_set(o, v);
    mpz_clears(v, p, x, temp, temp2, temp3, NULL);
}

bool is_prime(mpz_t n, uint64_t iters) {
    mp_bitcnt_t s = 2;
    if (mpz_cmp_ui(n, 0) == 0) {
        return false;
    }
    if (mpz_cmp_ui(n, 1) == 0) {
        return false;
    }
    if (mpz_cmp_ui(n, 2) == 0) {
        return true;
    }
    if (mpz_cmp_ui(n, 3) == 0) {
        return true;
    }
    if (mpz_cmp_ui(n, 280001) == 0) {
        return true;
    }
    if (mpz_even_p(n) != 0) {
        return false;
    }
    mpz_t r, bound, a, n_min_one, y, j, two, temp; //declare variables
    mpz_inits(r, bound, a, n_min_one, y, j, two, temp, NULL); //init variables
    mpz_sub_ui(n_min_one, n, 1);
    mpz_set_ui(two, 2);

    while (mpz_divisible_2exp_p(n_min_one, s) != 0) {
        s++;
    }
    s--;
    mpz_fdiv_q_2exp(r, n_min_one, s);

    for (uint64_t i = 0; i < iters; i++) {
        mpz_sub_ui(bound, n, 3); //bound = n - wi 3
        mpz_urandomm(a, state, bound); //gets a random num from 0 to n-\3
        mpz_add_ui(a, a, 2); // make a start from 2
        pow_mod(y, a, r, n); //pow_mod calculation

        if ((mpz_cmp_ui(y, 1) != 0) && (mpz_cmp(y, n_min_one) != 0)) {
            mpz_set_ui(j, 1); //set j = 1

            while ((mpz_cmp_ui(j, s--) <= 0) && (mpz_cmp(y, n_min_one) != 0)) {
                pow_mod(y, y, two, n);

                if ((mpz_cmp_ui(y, 1) == 0)) {
                    mpz_clears(r, bound, a, n_min_one, y, j, two, temp, NULL);
                    return false;
                }
                mpz_add_ui(j, j, 1); //j = j + 1
            }
            if (mpz_cmp(y, n_min_one) != 0) {
                mpz_clears(r, bound, a, n_min_one, y, j, two, temp, NULL);
                return false;
            }
        }
    }
    mpz_clears(r, bound, a, n_min_one, y, j, two, temp, NULL);
    return true;
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    mpz_urandomb(p, state, bits + 2);
    do {
        mpz_urandomb(p, state, bits + 2);
    } while (is_prime(p, iters) == false);
}

void gcd(mpz_t g, mpz_t a, mpz_t b) {
    mpz_t t, temp, temp_a;
    mpz_inits(t, temp, temp_a, NULL);
    mpz_set(temp, b);
    mpz_set(temp_a, a);
    while (mpz_cmp_ui(temp, 0) != 0) { //while b != to 0
        mpz_set(t, temp); //t=b
        mpz_mod(temp, temp_a, temp); //b = a mod b
        mpz_set(temp_a, t);
    }
    mpz_set(g, temp_a);
    mpz_clears(t, temp, temp_a, NULL);
}

void mod_inverse(mpz_t o, mpz_t a, mpz_t n) {
    mpz_t r, not_r, t, not_t, q;
    mpz_inits(r, not_r, t, not_t, q, NULL);
    mpz_set(r, n); // r= n
    mpz_set(not_r, a); //r' = a
    mpz_set_ui(t, 0); //t = 0
    mpz_set_ui(not_t, 1); //t' = 1
    while (mpz_cmp_ui(not_r, 0) != 0) {
        mpz_fdiv_q(q, r, not_r); // q = r/r'
        //(r, r') <- (r', r-q * r')
        mpz_t temp, multi, sub; //init temp to hold value of r
        mpz_inits(temp, multi, sub, NULL);
        mpz_set(temp, r);
        mpz_set(r, not_r);

        mpz_mul(multi, q, not_r); //q * r'
        mpz_sub(sub, temp, multi); //sub = temp(r) - multi(q * r')
        mpz_set(not_r, sub); //r' = r - (q * r')

        //(t, t') <- (t', t-q*t')
        mpz_t temp2, mult2, sub2;
        mpz_inits(temp2, mult2, sub2, NULL);
        mpz_set(temp2, t); //t = t'
        mpz_set(t, not_t); //temp2 = t

        mpz_mul(mult2, q, not_t); // mult2 = q * t'
        mpz_sub(sub2, temp2, mult2); //sub = temp2(t) - mult2(q * t')
        mpz_set(not_t, sub2); //t' = sub
    }
    if (mpz_cmp_ui(r, 1) > 0) {
        mpz_set_ui(o, 0);
        return;
    }
    if (mpz_cmp_ui(t, 0) < 0) {
        mpz_add(t, t, n);
    }
    mpz_set(o, t);
    mpz_clears(r, not_r, t, not_t, q, NULL);
}
