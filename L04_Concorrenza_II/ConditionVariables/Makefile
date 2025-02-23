CC = gcc
CFLAGS = -Wall -pedantic -std=c11
NAME = main
LIBS = -lpthread
OBJS = $(NAME).o lista.o

.PHONY: default clean

default: $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

run: $(NAME)
	./$(NAME)

clean:
	rm -f $(NAME) $(OBJS)
