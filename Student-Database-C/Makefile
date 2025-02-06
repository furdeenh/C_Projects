CC = gcc
CFLAGS = -Wall -Wextra

all: slist

slist: main.o slist.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c slist.h
	$(CC) $(CFLAGS) -c main.c

slist.o: slist.c slist.h
	$(CC) $(CFLAGS) -c slist.c

clean:
	rm -f slist *.o

.PHONY: all clean

