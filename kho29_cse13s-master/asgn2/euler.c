//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "mathlib.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t counter = 0;

double pi_euler(void) {
    double denum = 0;
    double tot = 0;
    double frac = 1;
    for (double i = 1; absolute(frac) > EPSILON; i++) {
        denum = i * i;
        frac = 1 / denum;
        tot += frac;
        counter += 1;
    }
    tot = 6 * tot;
    return (sqrt_newton(tot));
}

int pi_euler_terms(void) {
    return (counter);
}
