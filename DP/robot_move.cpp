#include <iostream>
#include <vector>
using namespace std;

// Function to calculate the number of unique paths in an m x n grid
int uniquePaths(int rows, int cols) {
    // Create a 2D DP table with dimensions rows x cols
    vector<vector<int>> pathCount(rows, vector<int>(cols, 1));
    
    // Iterate over the grid starting from cell (1,1)
    for (int row = 1; row < rows; row++) {
        for (int col = 1; col < cols; col++) {
            // The number of ways to reach (row, col) is the sum of ways from the top and left cells
            pathCount[row][col] = pathCount[row - 1][col] + pathCount[row][col - 1];
        }
    }
    
    // Return the value at the bottom-right corner, which is the total number of unique paths
    return pathCount[rows - 1][cols - 1];
}

int main() {
    int rows = 3, cols = 7; // Example input for a 3x7 grid
    cout << "Unique Paths: " << uniquePaths(rows, cols) << endl;
    return 0;
}
