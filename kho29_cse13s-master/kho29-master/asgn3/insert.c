//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "insert.h"

#include "set.h"
#include "stats.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//Function to call insertion sort on a array
//Takes in point to stats and array, and a uint32_t for length of array
//Psuedocode given in asgn3 pdf
void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (uint32_t i = 1; i < n; i += 1) {
        uint32_t j = i;
        uint32_t temp = A[i];
        while (j > 0 && cmp(stats, temp, A[j - 1]) < 0) {
            A[j] = A[j - 1];
            j -= 1;
            move(stats, n);
        }
        A[j] = temp;
        move(stats, n);
    }
}
