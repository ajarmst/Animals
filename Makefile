CC=gcc
CFLAGS=-g -Wall

all:main

main: main.o animals.o
	$(CC) main.o animals.o -o animals

main.o: main.c animals.c animals.h
	$(CC) $(CFLAGS) -c main.c

animals.o: animals.c animals.h
	$(CC) $(CFLAGS) -c animals.c

clean:
	rm -f *.o *~ animals

debug: all
	cgdb ./animals

ddd: all
	ddd ./animals
