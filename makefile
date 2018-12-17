CC = gcc
CFLAGS = -Wall -Werror

all: main

main: zad13.o days.o days.h
	$(CC) $(CFLAGS) -o out zad13.o days.o days.h

zad13.o: zad13.c
	$(CC) $(CFLAGS) -c zad13.c

days.o: days.c
	$(CC) $(CFLAGS) -c days.c

git:
	rm -rf *.o
	rm out

clean:
	rm -rf *.o

.PHONY: all clean git
