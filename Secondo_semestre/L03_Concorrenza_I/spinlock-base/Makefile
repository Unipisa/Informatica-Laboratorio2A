CC = gcc
CFLAGS = -pg -Wall -pedantic -std=c11
NAME = main
LIBS = -lpthread

.PHONY: run clean

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(NAME).o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

run: $(NAME)
	./$(NAME)

clean:
	rm -f $(NAME) $(NAME).o callgrind.out.* gmon.out
