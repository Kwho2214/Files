//Kwanchak Jason ho
//Cse13s Fall 2021

#include "stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//Provided in asgn4 pdf
struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t *items;
};

//provided in asgn4 pdf
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

//provided in asgn4 pdf
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

bool stack_empty(Stack *s) {
    return s->top == 0;
}

bool stack_full(Stack *s) {
    if (s->top == s->capacity) {
        return true;
    } else {
        return false;
    }
}

uint32_t stack_size(Stack *s) {
    return s->top;
}

bool stack_push(Stack *s, uint32_t x) {
    if (stack_full(s) == true) {
        return false;
    }
    //pushing stack
    s->items[s->top] = x;
    s->top += 1;
    return true;
}

bool stack_pop(Stack *s, uint32_t *x) {
    if (stack_empty(s) == true) {
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    return true;
}

bool stack_peek(Stack *s, uint32_t *x) {
    if (stack_empty(s) == true) {
        return false;
    }
    *x = s->items[s->top - 1];
    return true;
}

void stack_copy(Stack *dst, Stack *src) {
    if (dst->capacity == src->capacity) {
        for (uint32_t i = 0; i < src->top; i++) {
            dst->items[i] = src->items[i];
        }
        dst->top = src->top;
    }
}

//Was provided in asgn4 pdf
void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " - > ");
        }
    }
    fprintf(outfile, "\n");
}
/*
int main(void) {
	uint32_t x = 9;
	Stack *s = stack_create(x);
	x = x - 2;
	stack_push(s, x);
}
*/
