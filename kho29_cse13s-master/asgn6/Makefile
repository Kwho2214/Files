CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic $(shell pkg-config --cflags gmp)
LFLAGS = $(shell pkg-config --libs gmp)

all: encrypt decrypt keygen

encrypt: encrypt.o numtheory.o randstate.o rsa.o
	$(CC) encrypt.o numtheory.o randstate.o rsa.o -o encrypt $(LFLAGS)

decrypt: decrypt.o numtheory.o randstate.o rsa.o
	$(CC) decrypt.o numtheory.o randstate.o rsa.o -o decrypt $(LFLAGS)

keygen: keygen.o numtheory.o randstate.o rsa.o
	$(CC) keygen.o numtheory.o randstate.o rsa.o -o keygen $(LFLAGS)

encrypt.o: encrypt.c numtheory.c randstate.c rsa.c
	$(CC) $(CFLAGS) -c encrypt.c numtheory.c randstate.c rsa.c

decrypt.o: decrypt.c numtheory.c randstate.c rsa.c
	$(CC) $(CFLAGS) -c decrypt.c numtheory.c randstate.c rsa.c

keygen.o: keygen.c numtheory.c rsa.c randstate.c
	$(CC) $(CFLAGS) -c keygen.c numtheory.c randstate.c rsa.c

rsa.o: rsa.c numtheory.c
	$(CC) $(CFLAGS) -c rsa.c numtheory.c

numtheory.o: numtheory.c
	$(CC) $(CFLAGS) -c numtheory.c

randstate.o: randstate.c
	$(CC) $(CFLAGS) -c randstate.c

clean:
	rm -f numtheory.o randstate.o rsa.o encrypt.o decrypt.o keygen.o keygen encrypt decrypt

format:
	clang-format -i -style=file *.c *.h
