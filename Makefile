CFLAGS=-Wall -Wextra -Wformat=2 -Wno-format-nonliteral -Wshadow -Wpointer-arith -Wcast-qual -Wmissing-prototypes -Wno-missing-braces -std=gnu89 -D_GNU_SOURCE -O2 -pedantic-errors

all: main

main: main.o object.o stk.o
	gcc main.o object.o stk.o -o main

main.o: main.c
	gcc -c main.c

stk.o: stk.c
	gcc -c stk.c

object.o: object.c
	gcc -c object.c

clean:
	rm -rf main main.o object.o

