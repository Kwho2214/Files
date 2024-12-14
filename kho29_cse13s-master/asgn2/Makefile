CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

OBJECTS = bbp.o e.o euler.o madhava.o mathlib-test.o newton.o viete.o

all: mathlib-test

mathlib-test: mathlib-test.o e.o euler.o madhava.o viete.o bbp.o newton.o
	$(CC) $(LFLAGS) mathlib-test.o e.o euler.o madhava.o viete.o bbp.o newton.o -o mathlib-test

mathlib-test.o: mathlib-test.c mathlib.h
	$(CC) $(CFLAGS) -c mathlib-test.c

e.o: e.c mathlib.h
	$(CC) $(CFLAGS) -c e.c

euler.o: euler.c mathlib.h
	$(CC) $(CFLAGS) -c euler.c

madhava.o: madhava.c mathlib.h
	$(CC) $(CFLAGS) -c madhava.c

viete.o: viete.c mathlib.h
	$(CC) $(CFLAGS) -c viete.c

bbp.o: bbp.c mathlib.h
	$(CC) $(CFLAGS) -c bbp.c

newton.o: newton.c mathlib.h
	$(CC) $(CFLAGS) -c newton.c

clean:
	rm -f bbp.o e.o euler.o madhava.o mathlib-test.o newton.o viete.o mathlib-test

format:
	clang-format -i -style=file *.c *.h

