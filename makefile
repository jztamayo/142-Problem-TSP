CC = gcc
CFLAGS = -I include -Wall
tsp: src/main.c src/bruteforce.c src/optimize.c
	$(CC) $(CFLAGS) src/main.c src/bruteforce.c src/optimize.c -o tsp_solver