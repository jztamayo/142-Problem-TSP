#include <stdio.h>
#include <stdlib.h>
#include "../include/tsp.h"

// sources: 
//    https://rosettacode.org/wiki/Held%E2%80%93Karp_algorithm
//    https://www.youtube.com/watch?v=Q4zHb-Swzro&t=683s

int parent[MAX_CITIES][1 << MAX_CITIES];
int memo[MAX_CITIES][1 << MAX_CITIES];
int memo_set[MAX_CITIES][1 << MAX_CITIES]; // 0 = not computed, 1 = computed

void reconstruct(int starting_city, int num_cities){
    int path[MAX_CITIES];
    int unvisited = (1 << num_cities) - 1 & ~(1 << starting_city);
    int curr = starting_city;

    for (int step = 0; step < num_cities - 1; step++) {
        int next = parent[curr][unvisited];
        path[step] = next;
        unvisited = unvisited & ~(1 << next);
        curr = next;
    }

    printf("Optimal Path: %d -> ", starting_city);
    for (int step = 0; step < num_cities; step++){
        if ((step + 1) == num_cities){
            printf("%d\n", path[step]);
        } else {
            printf("%d -> ", path[step]);
        }
    }
}

int g(int starting_city, int curr_city, int num_cities, int unvisited, int matrix[MAX_CITIES][MAX_CITIES]){    
    // base case, if bitmap is empty
    if (unvisited == 0) {
        return matrix[curr_city][starting_city];
    }

    // return cached result if already computed
    if (memo_set[curr_city][unvisited]) {
        return memo[curr_city][unvisited];
    }

    int best_cost = 1e9; 
    for (int i=0; i<num_cities; i++) {
        if (unvisited & (1 << i)){
            int cost = matrix[curr_city][i] + g(starting_city, i, num_cities, unvisited & ~(1 << i), matrix); 
            if (cost < best_cost) {
                best_cost = cost;
                parent[curr_city][unvisited] = i;
            }
        }
    }

    // cache before returning
    memo[curr_city][unvisited] = best_cost;
    memo_set[curr_city][unvisited] = 1;

    return best_cost;

}

void solve_dynamic(int matrix[MAX_CITIES][MAX_CITIES], int num_cities){
    int starting_city = 0;

    // initialize memo table
    for (int i = 0; i < num_cities; i++)
        for (int j = 0; j < (1 << num_cities); j++)
            memo_set[i][j] = 0;

    int unvisited = ((1 << num_cities) - 1) & ~(1 << starting_city);
    int best_cost = g(starting_city, starting_city, num_cities, unvisited, matrix);
    
    printf("\nDYNAMIC PROGRAMMING SOLUTION: \n");
    printf("Cost of Optimal Path: %d\n", best_cost);

    reconstruct(starting_city, num_cities);
}

