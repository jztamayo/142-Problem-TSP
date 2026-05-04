CC = gcc
CFLAGS = -I include -Wall
tsp: src/main.c src/bruteforce.c src/optimize.c src/two_opt.c
	$(CC) $(CFLAGS) src/main.c src/bruteforce.c src/optimize.c src/two_opt.c -o tsp_solver