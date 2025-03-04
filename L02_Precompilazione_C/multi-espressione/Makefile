CC = gcc
CFLAGS = -Wall -pedantic
.PHONY: default clean

default:
	@echo "No, devi specificare make corretto o make errato"

corretto: corretto.o
	$(CC) $(CFLAGS) -o $@ $^

errato: errato.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f corretto errato corretto.o errato.o
