//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "mathlib.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t counter = 0;

double pi_bbp(void) {
    double term = 0;
    double numer = 1;
    double sixteen_pow = 16;
    double frac = 1;
    double t = 1;
    counter += 1;
    for (double i = 0; absolute(t) > EPSILON; i++) {
        frac = (i * (120 * i + 151) + 47);
        double bot = i * (i * (i * (512 * i + 1024) + 712) + 194) + 15;
        t = numer * frac / bot;
        term += t;
        counter += 1;
        numer = numer / sixteen_pow;
    }
    return (term);
}

int pi_bbp_terms(void) {
    return (counter);
}
