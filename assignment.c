#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
int is_positive_integer(const char *str) {
    if (str == NULL || *str == '\0') return 0; // Check if string is null or empty

    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return 0; // Check if each character is a digit
    }

    int value = atoi(str);
    return value > 0; // Check if the value is greater than 0
}

int main(int argc, char *argv[]) {
    // initialize random number generator
    srand(time(NULL));
    int minrand = 1;
    int maxrand = 100;

    // WRITE YOUR CODE HERE
   if (argc != 3) {
        printf("Incorrect usage. You provided %d arguments. The correct number of arguments is 2\n", argc - 1);
        return 1;
    }

    if (!is_positive_integer(argv[1]) || !is_positive_integer(argv[2])) {
        printf("Incorrect usage. The parameters you provided are not positive integers\n");
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    // Dynamically allocate a matrix
  
    // Allocate memory for the matrix
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        fprintf(stderr, "Failed to allocate memory for matrix\n");
        return 1;
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *) malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Failed to allocate memory for matrix row %d\n", i + 1);
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return 1;
        }
    }

    // Fill the matrix with random integers between 1 and 100
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = minrand + rand() % (maxrand - minrand + 1);
        }
    }

    // Write the matrix to a file named "matrix.txt"
    FILE *file = fopen("matrix.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file 'matrix.txt' for writing\n");
       
        for (int i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d", matrix[i][j]);
            if (j < cols - 1) {
                fprintf(file, " ");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);

    // Free dynamically allocated memory
   
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    
    return 0;
}
