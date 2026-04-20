CC = gcc
CFLAGS = -I include -Wall

tsp: src/main.c src/tsp.c
	$(CC) $(CFLAGS) src/main.c src/tsp.c -o tsp