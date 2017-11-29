CC=gcc
CFLAGS=-g -Wall

all:main

main: main.o animals.o util.o
	$(CC) main.o animals.o util.o -o animals

main.o: main.c animals.c animals.h
	$(CC) $(CFLAGS) -c main.c

animals.o: animals.c animals.h
	$(CC) $(CFLAGS) -c animals.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c

clean:
	rm -f *.o *~ animals

debug: all
	cgdb ./animals

ddd: all
	ddd ./animals
