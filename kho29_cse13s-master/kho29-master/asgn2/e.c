//Kwanchak Jason ho
//Cse13s Fall 2021

#include "mathlib.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//global variable
static uint32_t counter = 0;

double e(void) {
    double term = 1;
    double approx = 1;
    counter = 1;
    for (double i = 1; absolute(term) > EPSILON; i++) {
        term = term * (1 / i);
        approx = approx + term;
        counter += 1;
    }
    return (approx);
}

int e_terms(void) {
    return (counter);
}
