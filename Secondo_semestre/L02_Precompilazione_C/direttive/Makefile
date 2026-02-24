CC = gcc
CFLAGS = -Wall -pedantic
NAME = direttive

.PHONY: default clean

default: $(NAME)

$(NAME): $(NAME).o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(NAME) $(NAME).o
