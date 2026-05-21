VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS =-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -g
ENGINECFLAGS =-Wall -O0 -g
CC = gcc

all: clean valgrind-demo

valgrind-demo: demo
	valgrind $(VALGRIND_FLAGS) ./demo

engine:
	$(CC) $(ENGINECFLAGS) -c extra/engine.c -o engine.o

demo: engine
	$(CC) $(CFLAGS) main.c engine.o -o demo

clean:
	rm -f demo engine.o
