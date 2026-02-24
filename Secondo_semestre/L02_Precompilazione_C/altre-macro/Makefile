CC = gcc
CFLAGS = -Wall -pedantic
NAME = altre-macro

.PHONY: default clean

default: $(NAME)

$(NAME): $(NAME).o
	$(CC) $(CFLAGS) -o $@ $^

run: $(NAME)
	./$(NAME)

clean:
	rm -f $(NAME) $(NAME).o
