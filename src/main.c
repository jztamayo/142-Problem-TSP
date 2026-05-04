#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/tsp.h"

int best_cost = 1e9;
int best_path[MAX_CITIES];

int read_from_file(int matrix[MAX_CITIES][MAX_CITIES], int *num_cities) {
    char filename[50];
    char full_path[100];

    printf("Enter filename (.txt not needed): ");
    scanf("%s", filename);

    snprintf(full_path, sizeof(full_path), "data/%s.txt", filename);

    FILE *fp = fopen(full_path, "r");
    if (fp == NULL) {
        printf("Error: Could not open file %s\n", full_path);
        return 0;
    }

    // first row should be number of cities
    fscanf(fp, "%d", num_cities);

    for (int i = 0; i < *num_cities; i++) {
        for (int j = 0; j < *num_cities; j++) {
            if (fscanf(fp, "%d", &matrix[i][j]) != 1) {
                printf("Error: Invalid data format in file.\n");
                fclose(fp);
                return 0;
            }
        }
    }

    fclose(fp);
    return 1;
}

int main() {
    struct timespec time_before, time_after;
    int num_cities;
    int matrix[MAX_CITIES][MAX_CITIES];
    int choice, run_brute;
    printf("--- Travelling Salesman Problem Solver ---\n");

    printf("1. Manual Input\n");
    printf("2. Read from File\n");
    printf("Choice: ");
    scanf("%d", &choice);

    if (choice == 1){
        printf("Enter the number of cities: ");
        scanf("%d", &num_cities);

        if (num_cities > MAX_CITIES || num_cities < 2) {
            printf("Please enter a number between 2 and %d.\n", MAX_CITIES);
            return 1;
        }
        // the distance matrix
        printf("Enter the distance matrix (%d x %d):\n", num_cities, num_cities);
        for (int i = 0; i < num_cities; i++) {
            for (int j = 0; j < num_cities; j++) {
                printf("Distance from city %d to %d: ", i, j);
                scanf("%d", &matrix[i][j]);
            }
        }
    } else if (choice ==2){
        if (!read_from_file(matrix, &num_cities)) return 1;
    } else {
        printf("Invalid choice.\n");
    }
    
    printf("\n--- Matrix Loaded Successfully ---\n");
    // confirmation
    printf("\nLoaded %d cities. Matrix:\n", num_cities);
    for (int i = 0; i < num_cities; i++) {
        for (int j = 0; j < num_cities; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }

    /* TODO: 
       call solve_bruteforce(matrix, num_cities);
       call solve_optimized(matrix, num_cities);
       compare timing and results.
    */
   
    clock_gettime(CLOCK_MONOTONIC, &time_before);
    solve_dynamic(matrix, num_cities);
    clock_gettime(CLOCK_MONOTONIC, &time_after);
    double time_elapsed = (time_after.tv_sec - time_before.tv_sec) + 
                            (time_after.tv_nsec - time_before.tv_nsec) / 1e9;
    printf("Dynamic Execution time: %f\n", time_elapsed);

    printf("\n--- Running 2-Opt Heuristic ---\n");
    clock_gettime(CLOCK_MONOTONIC, &time_before);
    solve_2opt(matrix, num_cities);
    clock_gettime(CLOCK_MONOTONIC, &time_after);
    time_elapsed = (time_after.tv_sec - time_before.tv_sec) + 
                    (time_after.tv_nsec - time_before.tv_nsec) / 1e9;
    printf("2-Opt Execution time: %f\n", time_elapsed);

    printf("Run Bruteforce?\n");
    printf("1. Run\n");
    printf("0. Skip\n");
    printf("Choice: ");
    scanf("%d", &run_brute);

    if (run_brute == 1) {
        int visited[MAX_CITIES] = {0};
        int path[MAX_CITIES];

        // we start at city 0
        visited[0] = 1; 
        path[0] = 0;
        
        
        printf("\n--- Running Brute Force Solver ---\n");
        clock_gettime(CLOCK_MONOTONIC, &time_before);
        // we start at city 1 cause we visited 0 already
        solve_bruteforce(matrix, num_cities, visited, path, 0, 1, 0);

        printf("\nBRUTE FORCE SOLUTION:");
        printf("\nBest Cost: %d\n", best_cost);
        printf("Best Path: ");
        for (int i = 0; i < num_cities; i++) {
            printf("%d -> ", best_path[i]);
        }
        printf("0\n"); // return to city 0
        
        clock_gettime(CLOCK_MONOTONIC, &time_after);
        time_elapsed = (time_after.tv_sec - time_before.tv_sec) + 
                        (time_after.tv_nsec - time_before.tv_nsec) / 1e9;
        printf("Brute Force Execution time: %f s\n", time_elapsed);
    } else {
        printf("\nBrute Force skipped.\n");
    }

    return 0;
}