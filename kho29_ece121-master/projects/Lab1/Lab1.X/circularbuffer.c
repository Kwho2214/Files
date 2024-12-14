#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "circularbuffer.h"
#include "Protocol2.h"


void newbuffer(cbuffer *b){
    b->head = 0;
    b->tail = 0;
    b->overflow_count = 0;
}

void newPacketBuffer(pktbuff *p){
    p->head = 0;
    p->tail = 0;
    p->overflow_count = 0;
}

bool isfull(cbuffer *b){
    if((b->tail + 1) % SIZE == b->head){
        return true;
    }
    return false;
}

bool packetbuff_isfull(pktbuff *p){
    if((p->tail + 1) % SIZE == p->head){
        return true;
    }
    return false;
}

bool packetbuff_isempty(pktbuff *p){
    if(p->tail == p->head){
        return true;
    }
    return false;
}

bool isempty(cbuffer *b){
    if(b->tail == b->head){
        return true;
    }
    return false;
}

int enqueue(cbuffer* b, char chara){
    if(isfull(b)){
        b->overflow_count++;
        return 1;
    }else {
        b->buffer[b->tail] = chara;
        b->tail = (b->tail + 1) % SIZE;
        return 0;
    }
}

int packet_enqueue(pktbuff *p, rxpT *packet){
    if(packetbuff_isfull(p)){
        p->overflow_count++;
        return 1;
    }
    p->buffer[p->tail] = *packet;
    p->tail = (p->tail + 1) % PACKETBUFFERSIZE;
    return 0;
}

unsigned char dequeue(cbuffer *b){
    char value;
    if(!isempty(b)){
        value = b->buffer[b->head];
        //b->buffer[b->head] = NULL;
        b->head = (b->head + 1) % SIZE;
        return value;
    }else {
        return 0;
    }
}

rxpT packet_dequeue(pktbuff *p){
    rxpT packet;
    if(packetbuff_isempty(p)){
        // If the buffer is empty, return an empty packet
        packetinit(&packet); // Initialize the packet
        return packet;
    }
    packet = p->buffer[p->head];
    p->head = (p->head + 1) % PACKETBUFFERSIZE;
    return packet;
}