#ifndef TSP_H
#define TSP_H

#define MAX_CITIES 20
extern int best_cost;
extern int best_path[MAX_CITIES];

void solve_bruteforce(int matrix[MAX_CITIES][MAX_CITIES], int num_cities, int visited[], int path[], int curr_city, int count, int current_cost);
void solve_greedy(int matrix[MAX_CITIES][MAX_CITIES], int num_cities);

#endif