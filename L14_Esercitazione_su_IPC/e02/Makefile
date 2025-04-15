CC = gcc
CFLAGS = -std=c11 -Wall -pedantic
NAMEP = sender
NAMEC = receiver
LIBS = -lrt
OBJSP = $(NAMEP).o 
OBJSC = $(NAMEC).o

.PHONY: default clean

default: $(NAMEP) $(NAMEC)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NAMEP): $(OBJSP)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(NAMEC): $(OBJSC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

runp: $(NAMEP)
	./$(NAMEP)

runc: $(NAMEC)
	./$(NAMEC)
	

clean:
	rm -f $(NAMEP) $(OBJSP) $(NAMEC)  $(OBJSC)
