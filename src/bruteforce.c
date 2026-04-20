#include <stdio.h>
#include "../include/tsp.h"

// large number to represent infinity for the initial minimum
extern int best_cost; 
extern int best_path[MAX_CITIES];

void solve_bruteforce(int matrix[MAX_CITIES][MAX_CITIES], int num_cities, int visited[], int path[], int curr_city, int count, int current_cost) {
    
    // base case all cities have been visited
    if (count == num_cities) {
        // add distance from last city back to the starting city (city #0)
        int total_cost = current_cost + matrix[curr_city][0];
        
        if (total_cost < best_cost) {
            best_cost = total_cost;
            // record path as the best one found so far
            for (int i = 0; i < num_cities; i++) {
                best_path[i] = path[i];
            }
        }
        return;
    }

    // recursion: try every city connected
    for (int next_city = 0; next_city < num_cities; next_city++) {
        // if the city hasn't been visited and there is a path (>0)
        if (!visited[next_city] && matrix[curr_city][next_city] > 0) {
            
            // visit city
            visited[next_city] = 1;
            path[count] = next_city;

            // move to the next city
            solve_bruteforce(matrix, num_cities, visited, path, next_city, count + 1, current_cost + matrix[curr_city][next_city]);

            // backtrack
            visited[next_city] = 0;
        }
    }
}