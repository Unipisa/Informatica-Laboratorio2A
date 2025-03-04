CC = gcc
CFLAGS = -Wall -pedantic
OBJECTS = main.o utils.o

all: main

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o main $(OBJECTS)

main.o: main.c utils.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(OBJECTS) main
