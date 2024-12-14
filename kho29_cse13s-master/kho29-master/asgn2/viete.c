#include "mathlib.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//global variable
static uint32_t counter = 0;

double pi_viete(void) {
    double term = sqrt_newton(2);
    double frac = term / 2;
    double old = 0;
    double new = 1;
    counter = counter + 1;
    while (absolute(old - new) > EPSILON) {
        old = new;
        term = sqrt_newton(2 + term);
        new = new *term;
        frac *= term / 2;
        counter += 1;
    }
    return (2 / frac);
}

int pi_viete_factors(void) {
    return (counter);
}
