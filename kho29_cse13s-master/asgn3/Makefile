CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: sorting

sorting: heap.o insert.o quick.o shell.o stats.o sorting.o
	$(CC) $(LFLAGS) sorting.o heap.o insert.o quick.o shell.o stats.o -o sorting

sorting.o: sorting.c set.h
	$(CC) $(CFLAGS) -c sorting.c

heap.o: heap.c heap.h
	$(CC) $(CFLAGS) -c heap.c

insert.o: insert.c insert.h
	$(CC) $(CFLAGS) -c insert.c

quick.o: quick.c quick.h
	$(CC) $(CFLAGS) -c quick.c

shell.o: shell.c shell.h
	$(CC) $(CFLAGS) -c shell.c

stats.o: stats.c stats.h
	$(CC) $(CFLAGS) -c stats.c

clean:
	rm -f heap.o insert.o quick.o shell.o stats.o sorting.o sorting

format:
	clang-format -i -style=file *.c *.h
