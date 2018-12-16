CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: main

main: zad13.o days.o days.h
	$(CC) $(CFLAGS) -o out zad13.o days.o days.h

zad13.o: zad13.c
	$(CC) $(CFLAGS) -c zad13.c

days.o: days.c
	$(CC) $(CFLAGS) -c days.c

clean:
	rm -rf *.o

.PHONY: all clean
