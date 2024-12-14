/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "protocol2.h"

#define SIZE 1024

typedef struct cbufferobj{
    int head;
    int tail;
    int overflow_count;
    char buffer[SIZE];
}cbufferobj;

typedef struct cbufferobj cbuffer;

typedef struct pktbuffobj{
    int head;
    int tail;
    int overflow_count;
    rxpT buffer[PACKETBUFFERSIZE];
}pktbuffobj;

typedef struct pktbuffobj pktbuff;

void newbuffer(cbuffer *b);

void newPacketBuffer(pktbuff *p);

int enqueue(cbuffer *b, char chara);

// changed from rxpADT to rxpT

int packet_enqueue(pktbuff *p, rxpT *packet);

unsigned char dequeue(cbuffer *b);

rxpT packet_dequeue(pktbuff *p);

bool isfull(cbuffer *b);

bool isempty(cbuffer *b);

bool packetbuff_isfull(pktbuff *p);

bool packetbuff_isempty(pktbuff *p);
