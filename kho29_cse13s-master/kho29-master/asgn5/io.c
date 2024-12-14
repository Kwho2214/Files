//Kwanchak Jason Ho
//Cse13s Fall 2021

#include "io.h"
#include "header.h"
#include "code.h"
#include "defines.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static uint8_t buff[BLOCK] = { 0 };
static uint8_t code_buf[BLOCK] = { 0 };
static int code_ind = 0;
static int buf_ind = 0;

//to keep track of The stats
static int stats_read_bytes = 0;
int *global_read = &stats_read_bytes;
static int stats_written_bytes = 0;
int *global_wrote = &stats_written_bytes;

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int num_bytes = 0; //how many we have read so far
    int total_read = 0; //total bytes read
    int bytes_read = 0;
    while ((bytes_read = read(infile, buf, nbytes)) > 0 && nbytes != 0) {
        total_read += bytes_read; //increase what we have read
        nbytes -= bytes_read; //decrease number of bytes we are suppose to read
        num_bytes += bytes_read; //increase bytes read
        buf += bytes_read; //increase buf
    }
    stats_read_bytes += bytes_read;
    return total_read; //return total read
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int num_bytes = 0; //how many we have written
    int total_writ = 0; //total written bytes
    int wrote = 0;
    while ((wrote = write(outfile, buf, nbytes)) > 0 && nbytes != 0) {
        total_writ += wrote; //increase total with how much we wrote
        nbytes -= wrote; //decrease how much we need to write with how many written
        buf += wrote; //increase buf with how much wrote
        num_bytes += wrote;
    }
    stats_written_bytes += wrote;
    return total_writ; //return total written
}

//Psuedo code from Eugene's Section
bool read_bit(int infile, uint8_t *bit) {
    static int end_of_bit = -1; //tracks last valid bit
    if (buf_ind == 0) {
        int bytes_read = read_bytes(infile, buff, BLOCK);
        if (bytes_read < BLOCK) {
            //set end of bit
            end_of_bit = bytes_read * 8 + 1;
        }
    }
    //get bit from buffer at the index
    *bit = (buff[buf_ind / 8] >> (buf_ind % 8)) & 1;
    buf_ind += 1;
    if (buf_ind == BLOCK * 8) { //if index is max
        buf_ind = 0; //reset index
    }
    return buf_ind != end_of_bit;
}

void write_code(int outfile, Code *c) {
    for (uint32_t i = 0; i < code_size(c); i++) { //buffer each bit into buffer using loop
        int bit = (code_buf[code_ind / 8] >> (code_ind % 8)) % 1; //gets bit
        if (bit == 1) { //if bit is 1 sets the bit
            code_buf[code_ind / 8] |= (1 << (code_ind % 8));
        } else { //else clears the bit
            code_buf[code_ind / 8] &= ~(1 << (code_ind % 8));
        }
        if (code_ind == BLOCK * 8) { //when buffer full, writes to outfile
            write_bytes(outfile, code_buf, BLOCK);
            code_ind = 0;
        }
    }
}

void flush_codes(int outfile) {
    if (code_ind > 0) {
        write_bytes(outfile, code_buf, code_ind / 8);
    }
}
