CC = gcc
CFLAGS = -Wall -pedantic
DEBUG_FLAGS = -g $(CFLAGS)
RELEASE_FLAGS = -O3 $(CFLAGS)
OBJECTS = main.o

all: debug release

main: $(OBJECTS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

debug: main
	$(CC) $(DEBUG_FLAGS) main.o -o debug

release: main
	$(CC) $(RELEASE_FLAGS) main.o -o release
	zip release.zip release

clean:
	rm -f $(OBJECTS) main debug release release.zip

.PHONY: debug release clean

