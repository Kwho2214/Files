//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "mathlib.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t counter = 0;

double sqrt_newton(double x) {
    double z = 0;
    double y = 1;
    while (absolute(y - z) > EPSILON) {
        z = y;
        y = 0.5 * (z + x / z);
        counter += 1;
    }
    return (y);
}

int sqrt_newton_iters(void) {
    return (counter);
}
