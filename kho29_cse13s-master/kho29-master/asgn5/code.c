//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "code.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Code code_init(void) {
    Code c; //initalize code
    c.top = 0; //top of code is 0
    for (int i = 0; i < MAX_CODE_SIZE; i++) { //iterate through to set bits to 0
        c.bits[i] = 0;
    }
    return c; //return the code
}

uint32_t code_size(Code *c) {
    return c->top; //returns the code size
}

bool code_empty(Code *c) {
    if (code_size(c) == 0) { //if size of code is 0, empty
        return true;
    } else {
        return false;
    }
}

bool code_full(Code *c) {
    if (code_size(c) == ALPHABET) { //if size is ALPHABET then its full
        return true;
    } else {
        return false;
    }
}

bool code_set_bit(Code *c, uint32_t i) {
    return (c->bits[i / 8] |= 1 << (c->top % 8));
}

bool code_clr_bit(Code *c, uint32_t i) {
    return (c->bits[i / 8] &= ~(1 << (c->top % 8)));
}

bool code_get_bit(Code *c, uint32_t i) {
    return (c->bits[i / 8] >> i % 8) & 1;
}

bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c) == true) {
        return false;
    }
    // if 1 set bit if 0 clear
    if (bit == 1) {
        code_set_bit(c, c->top);
    } else {
        code_clr_bit(c, c->top);
    }
    c->top += 1;
    return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c) == true) {
        return false;
    }
    //get bit then put into *bit
    c->top -= 1;
    *bit = (c->bits[c->top / 8] >> (c->top % 8)) & 1;
    return true;
}

void code_print(Code *c) {
    //to print the code
    for (uint32_t i = 0; i < c->top; i++) {
        printf("%c\n", c->bits[i]);
    }
}
