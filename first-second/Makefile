CC = /usr/bin/gcc
CFLAGS = -Wall -g

all: first second

first: $(OBJ1)
	$(CC) $(CFLAGS) -o first first.c

second: $(OBJ2)
	$(CC) $(CFLAGS) -o second second.c

clean:
	rm -f *.o first second out.*
