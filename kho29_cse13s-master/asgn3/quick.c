//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "quick.h"

#include "stats.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

//Psuedo code was provided in asgn3 pdf
//Partition function to place element less than pivot to it's left
//and elements to it's right
int64_t partition(Stats *stats, uint32_t *A, int64_t lo, int64_t hi) {
    int64_t i = lo - 1;
    for (int64_t j = lo; j < hi; j++) {
        if (cmp(stats, A[j - 1], A[hi - 1]) == -1) {
            i += 1;
            swap(stats, &A[i - 1], &A[j - 1]);
        }
    }
    swap(stats, &A[i], &A[hi - 1]);
    return (i + 1);
}

//A function to do quick_sort recursively
void quick_sorter(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    if (lo < hi) {
        int64_t p = partition(stats, A, lo, hi);
        quick_sorter(stats, A, lo, p - 1);
        quick_sorter(stats, A, p + 1, hi);
    }
}

//Fucntion for quick_sort, using recursive calling.
void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(stats, A, 1, n);
}
