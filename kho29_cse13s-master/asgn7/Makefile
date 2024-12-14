CC = clang
CFLAGS = -Wall -Werror -Wpedantic -Wextra
LFLAGS = -lm

all: banhammer

banhammer: bf.o bv.o bst.o node.o ht.o parser.o speck.o banhammer.o banhammer 
	$(CC) $(CFLAGS) bf.o bv.o bst.o node.o ht.o parser.o speck.o banhammer.o -o banhammer $(LFLAGS)

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

bf.o: bf.c bv.c
	$(CC) $(CFLAGS) -c bf.c bv.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

bst.o: bst.c node.c
	$(CC) $(CFLAGS) -c bst.c node.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

ht.o: ht.c node.c
	$(CC) $(CFLAGS) -c ht.c node.c

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c

clean:
	rm -f banhammer banhammer.o bst.o bv.o bf.o node.o ht.o parser.o speck.o

format:
	clang-format -i -style=file *.c *.h
