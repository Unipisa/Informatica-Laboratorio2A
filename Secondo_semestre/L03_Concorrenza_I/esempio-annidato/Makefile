CC = gcc
CFLAGS = -Wall -pedantic -std=c11
NAME = main
LIBS = -lpthread

.PHONY: default clean

default: $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(NAME).o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

run: $(NAME)
	./$(NAME)

clean:
	rm -f $(NAME) $(NAME).o
