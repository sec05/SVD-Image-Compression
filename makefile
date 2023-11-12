CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: main

main: main.o matrix.o
	$(CC) $(CFLAGS) -o main main.o matrix.o

main.o: main.c matrix.h
	$(CC) $(CFLAGS) -c main.c

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c

clean:
	rm -f main main.o matrix.o
