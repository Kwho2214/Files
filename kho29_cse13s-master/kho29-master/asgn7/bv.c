//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "bv.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

//I looked at Professor Long's bv8.h

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector)); //allocate memory for bitvector
    if (bv) {
        bv->length = length; //length of bitvector
        bv->vector = (uint8_t *) calloc(length, sizeof(uint8_t)); //allocate memory for the array
        return bv;
    }
    return bv;
}

void bv_delete(BitVector **bv) {
    free((*bv)->vector);
    free(*bv);
    *bv = NULL;
}

uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

bool bv_set_bit(BitVector *bv, uint32_t i) {
    if (i > bv->length) {
        return false;
    }
    if (bv) {
        return bv->vector[i / 8] |= (0x1 << i % 8);
    } else {
        return false;
    }
}

bool bv_clr_bit(BitVector *bv, uint32_t i) {
    if (i > bv->length) {
        return false;
    }
    if (bv) {
        return (bv->vector[i / 8] &= ~(0x1 << (i % 8)));
    } else {
        return false;
    }
}

bool bv_get_bit(BitVector *bv, uint32_t i) {
    if (i > bv->length) {
        return false;
    }
    if (bv) {
        return (bv->vector[i / 8] >> i % 8) & 0x1;
    } else {
        return false;
    }
}

void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < bv->length; i += 1) {
        uint8_t bit = bv->vector[i];
        printf("The %dth bit is: %d\n", i, bit);
    }
}
