CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: tsp

tsp: graph.o stack.o path.o tsp.o
	$(CC) $(CFLAGS) $(LFLAGS) graph.o stack.o path.o tsp.o -o tsp

tsp.o: tsp.c vertices.h
	$(CC) $(CFLAGS) -c tsp.c

graph.o: graph.c vertices.h
	$(CC) $(CFLAGS) -c graph.c

stack.o: stack.c vertices.h
	$(CC) $(CFLAGS) -c stack.c

path.o: path.c vertices.h stack.c graph.c
	$(CC) $(CFLAGS) -c path.c stack.c graph.c

clean:
	rm -f graph.o path.o stack.o tsp.o tsp

format:
	clang-format -i -style=file *.c *.h
