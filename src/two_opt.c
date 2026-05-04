#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/tsp.h"

// Calculates the total cost of a given path
int calculate_path_cost(int matrix[MAX_CITIES][MAX_CITIES], int path[], int num_cities) {
    int cost = 0;
    for (int i = 0; i < num_cities - 1; i++) {
        cost += matrix[path[i]][path[i+1]];
    }
    cost += matrix[path[num_cities-1]][path[0]]; // Back to start
    return cost;
}

// Reverses a segment of the path from index i to k
void reverse_segment(int path[], int i, int k) {
    while (i < k) {
        int temp = path[i];
        path[i] = path[k];
        path[k] = temp;
        i++;
        k--;
    }
}

// Main Two-opt function
void solve_2opt(int matrix[MAX_CITIES][MAX_CITIES], int num_cities) {
    int path[MAX_CITIES];
    bool visited[MAX_CITIES] = {0};

    // Use Greedy to generate an initial valid route
    int curr = 0;
    path[0] = curr;
    visited[curr] = true;

    for (int i = 1; i < num_cities; i++) {
        int nearest = -1;
        int min_dist = 1e9;
        for (int next = 0; next < num_cities; next++) {
            if (!visited[next] && matrix[curr][next] < min_dist) {
                min_dist = matrix[curr][next];
                nearest = next;
            }
        }
        path[i] = nearest;
        visited[nearest] = true;
        curr = nearest;
    }

    // Greedy Algorithim Results
    int initial_cost = calculate_path_cost(matrix, path, num_cities);
    printf("\nGREEDY SOLUTION:\n");
    printf("Greedy Cost: %d\n", initial_cost);
    printf("Greedy Path: ");
    for (int i = 0; i < num_cities; i++) printf("%d -> ", path[i]);
    printf("%d\n", path[0]);

    // Two-opt Optimization
    bool improvement = true;
    int swaps = 0; 
    while (improvement) {
        improvement = false;

        for (int i = 1; i < num_cities - 1; i++) {
            for (int k = i + 1; k < num_cities; k++) {
                
                // Loop back through the list of cities
                int k_next = (k + 1) % num_cities;

                // Compare gain                
                int current_dist = matrix[path[i-1]][path[i]] + matrix[path[k]][path[k_next]];
                int new_dist = matrix[path[i-1]][path[k]] + matrix[path[i]][path[k_next]];

                if (new_dist < current_dist) {
                    reverse_segment(path, i, k);
                    improvement = true;
                    swaps++;
                }
            }
        }
    }

    // Output
    printf("\n2-OPT HEURISTIC SOLUTION:\n");
    printf("Approximate Cost: %d\n", calculate_path_cost(matrix, path, num_cities));
    printf("Improvements Made: %d swaps\n", swaps);
    printf("Path: ");
    for (int i = 0; i < num_cities; i++) {
        printf("%d -> ", path[i]);
    }
    printf("%d\n", path[0]);
}