#include <stdio.h>
#include <stdlib.h>

// max matrix size
#define MAX_CITIES 20

int read_from_file(int matrix[MAX_CITIES][MAX_CITIES], int *num_cities) {
    char filename[100];
    printf("Enter filename (e.g., test.txt): ");
    scanf("%s", filename);

    // sprintf(full_path, "data/%s", filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Could not open file %s\n", filename);
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
    int num_cities;
    int matrix[MAX_CITIES][MAX_CITIES];
    int choice;



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
       call solve_brute_force(matrix, num_cities);
       call solve_optimized(matrix, num_cities);
       compare timing and results.
    */

    return 0;
}