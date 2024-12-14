//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "pq.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

struct PriorityQueue {
    uint32_t tail;
    uint32_t head;
    uint32_t capacity;
    uint32_t size;
    Node **heap;
};

//Swaps nodes
void swap(Node **x, Node **y) {
    Node *temp = *x;
    *x = *y;
    *y = temp;
}

uint32_t left_child(uint32_t i) {
    return (2 * i);
}

uint32_t right_child(uint32_t i) {
    return ((2 * i) + 1);
}

uint32_t parent(uint32_t i) {
    return (i / 2);
}

//fixes heap
void minimum_heap(PriorityQueue *q, uint32_t i) {
    uint32_t left = left_child(i);
    uint32_t right = right_child(i);
    uint32_t least = 0;
    if ((left <= q->size) && (q->heap[left]->frequency < q->heap[i]->frequency)) {
        least = left;
    } else {
        least = i;
    }
    if ((right <= q->size) && (q->heap[right]->frequency < q->heap[least]->frequency)) {
        least = right;
    }
    if (least != i) {
        swap(&q->heap[least], &q->heap[i]);
        minimum_heap(q, least);
    }
}

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) calloc(capacity, sizeof(PriorityQueue));
    q->tail = 0;
    q->head = 0;
    q->capacity = capacity;
    q->size = 0;
    //capacity + 1 to start a index 1 and not index 0
    q->heap = (Node **) calloc(capacity + 1, sizeof(Node *));
    return q;
}

void pq_delete(PriorityQueue **q) {
    for (uint32_t i = 0; i < (*q)->capacity; i++) {
        free((*q)->heap[i]);
    }
    free(*q);
    *q = NULL;
}

bool pq_empty(PriorityQueue *q) {
    if (q->tail == 0) {
        return true;
    } else {
        return false;
    }
}

bool pq_full(PriorityQueue *q) {
    if (q->size == q->capacity) {
        return true;
    } else {
        return false;
    }
}

uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}

bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full(q) == true) {
        return false;
    }
    //enqueue
    uint32_t i = q->size + 1;
    uint32_t parent_node = parent(i);
    q->heap[i] = n;
    while (i > 1 && q->heap[parent_node]->frequency > q->heap[i]->frequency) {
        swap(&q->heap[parent_node], &q->heap[i]);
        i = parent_node;
        parent_node = parent(i);
    }
    q->size += 1;
    q->head += 1;
    return true;
}

bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q) == true) {
        return false;
    }
    //dequeue
    Node *small = q->heap[q->tail];
    q->heap[q->tail] = q->heap[q->size];
    q->size -= 1;
    q->tail += 1;
    //fix heap
    minimum_heap(q, q->tail);
    *n = small;
    return true;
}

void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0; i < q->capacity; i++) {
        node_print(q->heap[i]);
    }
}
