//Kwwanchak Jason Ho
//Cse13s Fall 2021

#include "mathlib.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t counter = 0;

double pi_madhava(void) {
    double term = 1;
    double numer = 1;
    double x = -3;
    double frac = 1;
    counter = counter + 1;
    for (double i = 1; absolute(frac) > EPSILON; i++) {
        numer = numer * x;
        double inv = 1 / numer;
        double denum = (2 * i + 1);
        frac = inv / denum;
        term += frac;
        counter += 1;
    }
    term = sqrt_newton(12) * term;
    return (term);
}

int pi_madhava_terms(void) {
    return (counter);
}
