#ifndef TSP_H
#define TSP_H

#define MAX_CITIES 15

void solve_brute_force(int matrix[MAX_CITIES][MAX_CITIES], int num_cities);
void solve_greedy(int matrix[MAX_CITIES][MAX_CITIES], int num_cities);

#endif