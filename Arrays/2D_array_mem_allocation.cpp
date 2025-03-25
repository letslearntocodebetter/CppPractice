#include <stdio.h>
#include <stdlib.h>

// Method 1: Two-step malloc - Allocate pointer array first, then allocate each row
int** allocate_2d_array_method1(int rows, int cols) {
    // Step 1: Allocate an array of pointers (one for each row)
    int** array = (int**)malloc(rows * sizeof(int*));
    
    // Error checking for initial allocation
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed for row pointers\n");
        return NULL;
    }
    
    // Step 2: Allocate memory for each row separately
    for (int i = 0; i < rows; i++) {
        // Allocate memory for each row with the specified number of columns
        array[i] = (int*)malloc(cols * sizeof(int));
        
        // Error checking for each row allocation
        if (array[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for row %d\n", i);
            
            // Free previously allocated rows before returning
            for (int j = 0; j < i; j++) {
                free(array[j]);
            }
            free(array);
            return NULL;
        }
    }
    
    return array;
}

// Method 2: Single malloc - Allocate entire 2D array in one contiguous block
int** allocate_2d_array_method2(int rows, int cols) {
    // Allocate memory for row pointers PLUS the actual data in one contiguous block
    // Total allocation: (rows * sizeof(pointer) + rows * cols * sizeof(int))
    int** array = malloc(rows * sizeof(int*) + rows * cols * sizeof(int));
    
    // Error checking for allocation
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    
    // Set up pointers to point to the correct locations in the contiguous memory block
    // The actual data starts after the pointer array
// First rows * sizeof(int*) bytes are reserved for the pointer array
// Immediately following that, rows * cols * sizeof(int) bytes are reserved for the actual integer data


    for (int i = 0; i < rows; i++) {
        // Point each row pointer to the correct offset in the memory block
        array[i] = (int*)(array + rows) + i * cols;
    }
    
    return array;
}

// Utility function to free memory for Method 1
void free_2d_array_method1(int** array, int rows) {
    // Free each row first
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    // Then free the pointer array
    free(array);
}

// Utility function to free memory for Method 2
void free_2d_array_method2(int** array) {
    // Single free since it was allocated in one block
    free(array);
}