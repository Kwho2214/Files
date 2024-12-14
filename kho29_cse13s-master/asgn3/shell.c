//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "shell.h"

#include "stats.h"

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

//A function to calculate the gaps for the shell sort
//takes in a uint32_t, which should be length of array.
//Christian's section told us to type cast it and floor the return
uint32_t gaps(uint32_t n) {
    static uint32_t start_iter = 0;
    if (start_iter <= 0) {
        start_iter = (uint32_t)(log(3 + 2 * n) / log(3));
    } else {
        start_iter -= 1;
    }
    return (uint32_t) floor((((pow(3, start_iter)) - 1) / 2));
}

//Shell sort function, takes in a pointer to stats
//a pointer to the array and a uint32_t number for the length of array
//Psuedo code given to us in asgn3 pdf
void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t big_k = (uint32_t)(log((2 * n + 3)) / log(3));
    for (uint32_t g = 0; g < big_k; g++) {
        uint32_t gap = gaps(n);
        for (uint32_t i = gap; i < n; i++) {
            uint32_t j = i;
            uint32_t temp = A[i];
            while (j >= gap && cmp(stats, temp, A[j - gap]) == -1) {
                A[j] = A[j - gap];
                j -= gap;
                move(stats, n);
            }
            A[j] = temp;
            move(stats, n);
        }
    }
}
