CC = gcc
CFLAGS = -Wall -pedantic
NAME = macro-annidate

.PHONY: default clean

default: $(NAME)

$(NAME): $(NAME).o
	$(CC) $(CFLAGS) -o $@ $^

run: $(NAME)
	./$(NAME)

clean:
	rm -f $(NAME) $(NAME).o
