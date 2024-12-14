//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define options       "aeisqr:n:p:h"
#define default_seed  13371453
#define default_size  100
#define default_print 100
#define MASK          30

typedef enum { insert, shell, heap, quick } sort;

void instruct(void) {
    printf("SYNOPSIS\n");
    printf("   A collection of comparison-based sorting algorithms.\n");
    printf("\n");
    printf("USAGE\n");
    printf("   ./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("   -h              display program help and usage.\n");
    printf("   -a              enable all sorts.\n");
    printf("   -e              enable Heap Sort.\n");
    printf("   -i              enable Insertion Sort.\n");
    printf("   -s              enable Shell Sort.\n");
    printf("   -q              enable Quick Sort.\n");
    printf("   -n length       specify number of array elements (default: 100).\n");
    printf("   -p elements     specify number of elements to print (default: 100).\n");
    printf("   -r seed         specify random seed (default: 13371453).\n");
}

//A function to print the array.
//the for loop was given in a link from class discord
//that took us to stackoverflow
void print_arr(uint32_t *A, uint32_t num_elem, uint32_t size) {
    uint32_t cols = 0;
    if (num_elem > size) {
        num_elem = size;
    }
    for (uint32_t d = 0; d < num_elem; d++) {
        printf("%13" PRIu32, A[d]);
        cols += 1;
        if (cols == 5) {
            cols = 0;
            printf("\n");
        }
    }
}

int main(int argc, char **argv) {
    /*
    Stats stats;
    stats.moves = 0;
    stats.compares = 0;

    uint32_t A[5] = { 5, 3, 1, 4, 2 };
    shell_sort(&stats, A, 5);
    for (uint32_t i = 0; i < 5; i++) {
        printf("%" PRIu32, A[i]);
    }
    printf("moves = %" PRIu64, stats.moves);
    printf(" compares = %" PRIu64 "\n", stats.compares);
    */
    int opt = 0;
    uint32_t seed = default_seed;
    uint32_t size = default_size;
    uint32_t num_elem = default_print;

    Set s = empty_set();

    while ((opt = getopt(argc, argv, options)) != -1) {
        switch (opt) {
        case 'a':
            for (uint32_t o = 0; o < 4; o++) {
                s = insert_set(o, s);
            }
            break;
        case 'e': s = insert_set(heap, s); break;
        case 'i': s = insert_set(insert, s); break;
        case 's': s = insert_set(shell, s); break;
        case 'q': s = insert_set(quick, s); break;
        case 'r': seed = atoi(optarg); break;
        case 'n': size = atoi(optarg); break;
        case 'p': num_elem = atoi(optarg); break;
        case 'h': instruct(); break;
        }
    }
    uint32_t *A = (uint32_t *) calloc(size, sizeof(uint32_t));
    // forloop for calling the sorts
    for (uint32_t i = 0; i < 4; i++) {
        if (member_set(i, s)) {
            Stats stats;
            reset(&stats);
            srandom(seed);
            for (uint32_t j = 0; j < size; j++) {
                A[j] = random() & ((long) 1 << MASK) - 1;
            }
            switch (i) {
            case 0:
                insertion_sort(&stats, A, size);
                printf("Insert Sort  ");
                if (num_elem == 0) {
                    printf("elements %d ", default_print);
                } else {
                    printf("elements %d ", size);
                }
                printf(" move ");
                printf("%" PRIu64, stats.moves);
                printf(" compare ");
                printf("%" PRIu64 "\n", stats.compares);
                print_arr(A, num_elem, size);
                break;
            case 1:
                shell_sort(&stats, A, size);
                printf("Shell Sort  ");
                if (num_elem == 0) {
                    printf("elements %d ", size);
                } else {
                    printf("elements %d ", size);
                }
                printf(" move ");
                printf("%" PRIu64, stats.moves);
                printf(" compare ");
                printf("%" PRIu64 "\n", stats.compares);
                print_arr(A, num_elem, size);
                break;
            case 2:
                heap_sort(&stats, A, size);
                printf("Heap Sort  ");
                if (num_elem == 0) {
                    printf("elements %d ", size);
                } else {
                    printf("elements %d ", size);
                }
                printf(" move ");
                printf("%" PRIu64, stats.moves);
                printf(" compare ");
                printf("%" PRIu64 "\n", stats.compares);
                print_arr(A, num_elem, size);
                break;
            case 3:
                quick_sort(&stats, A, size);
                printf("Quick Sort ");
                if (num_elem == 0) {
                    printf("elements %d ", size);
                } else {
                    printf("elements %d", size);
                }
                printf(" move ");
                printf("%" PRIu64, stats.moves);
                printf(" compare ");
                printf("%" PRIu64 "\n", stats.compares);
                print_arr(A, num_elem, size);
                break;
            }
            reset(&stats);
        }
        delete_set(0, s);
        delete_set(1, s);
        delete_set(2, s);
        delete_set(3, s);
    }
    free(A);
    A = NULL;
    return 0;
}
