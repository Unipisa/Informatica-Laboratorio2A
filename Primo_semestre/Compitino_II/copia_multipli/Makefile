CC = gcc
CFLAGS = -Wall -pedantic
OBJECTS = main.o
all: main

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJECTS) main

