CC = clang
CFLAGS = -Werror -Wpedantic -Wall -Wextra
LFLAGS = -lm

all: encode decode

encode: io.o node.o stack.o pq.o encode.o huffman.o code.o
	$(CC) $(LFLAGS) $(CFLAGS) io.o node.o stack.o pq.o huffman.o encode.o code.o -o encode

decode: io.o node.o stack.o pq.o decode.o huffman.o code.o
	$(CC) $(LFLAGS) $(CFLAGS) io.o node.o stack.o pq.o huffman.o decode.o code.o -o decode

encode.o: encode.c pq.c io.c code.c huffman.c stack.c node.c
	$(CC) $(CFLAGS) -c encode.c pq.c code.c io.c huffman.c stack.c node.c

decode.o: decode.c stack.c io.c code.c huffman.c node.c pq.c
	$(CC) $(CFLAGS) -c decode.c stack.c io.c code.c huffman.c node.c pq.c

huffman.o: huffman.c pq.c node.c stack.c code.c io.c
	$(CC) $(CFLAGS) -c huffman.c pq.c node.c stack.c code.c io.c

io.o: io.c code.c defines.h
	$(CC) $(CFLAGS) -c io.c code.c

code.o: code.c
	$(CC) $(CFLAGS) -c code.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c

clean:
	rm -rf node.o io.o pq.o code.o stack.o huffman.o encode.o decode.o decode encode

format:
	clang-format -i -style=file *.c *.h
