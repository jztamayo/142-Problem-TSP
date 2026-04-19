#include <stdio.h>
#include <stdlib.h>

// max matrix size
#define MAX_CITIES 20

int main() {
    int num_cities;
    int matrix[MAX_CITIES][MAX_CITIES];

    printf("--- Travelling Salesman Problem Solver ---\n");
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

    printf("\n--- Matrix Loaded Successfully ---\n");
    // confirmation
    for (int i = 0; i < num_cities; i++) {
        for (int j = 0; j < num_cities; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    /* TODO: 
       call solve_brute_force(matrix, num_cities);
       call solve_optimized(matrix, num_cities);
       compare timing and results.
    */

    return 0;
}