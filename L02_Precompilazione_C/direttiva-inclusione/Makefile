CC = gcc
CFLAGS = -Wall -pedantic
NAME = main

.PHONY: default clean

default: $(NAME)

$(NAME): $(NAME).o modulo1.o modulo2.o
	$(CC) $(CFLAGS) -o $@ $^ 

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	rm -f $(NAME) $(NAME).o *.o
