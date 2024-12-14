//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "bf.h"
#include "salts.h"
#include "bv.h"
#include "speck.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

struct BloomFilter {
    uint64_t primary[2]; //Primary hash function salt.
    uint64_t secondary[2]; //Secondary hash function salt
    uint64_t tertiary[2]; //Tertiary hash function salt
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) calloc(size, sizeof(BloomFilter)); //allocate memory for bf
    bf->primary[0] = SALT_PRIMARY_LO; //set first half of primary to index 0
    bf->primary[1] = SALT_PRIMARY_HI; //set second half to index 1

    bf->secondary[0] = SALT_SECONDARY_LO; //set first half of secondary to index 0
    bf->secondary[1] = SALT_SECONDARY_LO; //set second half of secondary to index 1

    bf->tertiary[0] = SALT_TERTIARY_LO; //set first half of tertiary to index 0
    bf->tertiary[1] = SALT_TERTIARY_HI; //set second half of tertiary to index 1
    bf->filter = bv_create(size); //make the filter using bv_create
    return bf;
}

void bf_delete(BloomFilter **bf) {
    bv_delete(&(*bf)->filter); //free filter's memory
    free(*bf); //free bloomfilter
    *bf = NULL;
}

uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    bv_set_bit(
        bf->filter, hash(bf->primary, oldspeak) % bf_size(bf)); //place oldspeak into bloomfilter
    bv_set_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf));
    bv_set_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf));
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    return bv_get_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf))
           & bv_get_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf))
           & bv_get_bit(
               bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf)); //to see if in bloomfilter
}

uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < bv_length(bf->filter); i += 1) {
        if (bv_get_bit(bf->filter, i) == true) {
            count += 1;
        }
    }
    return count;
}

void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}
