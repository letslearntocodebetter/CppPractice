/** 
  498. Diagonal Traverse
Thought Process and Strategy
This problem requires us to traverse a matrix diagonally, starting from the top-left element and alternating between moving upward and downward along diagonals.

Key observations:

Elements on the same diagonal have indices (i,j) where i+j is constant
An m×n matrix has m+n-1 diagonals
Direction alternates with each diagonal:
Even-numbered diagonals: move upward (decrease row, increase column)
Odd-numbered diagonals: move downward (increase row, decrease column)
*/


class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        // Handle empty matrix case
        if (matrix.empty()) {
            return {};
        }
        
        int numRows = matrix.size();
        int numCols = matrix[0].size();
        vector<int> traversalResult;
        
        // In a matrix, all elements where row+col = constant form a diagonal
        // Total number of diagonals = numRows + numCols - 1
        // Example: For a 3x3 matrix, we have 5 diagonals:
        // Diagonal 0: (0,0)
        // Diagonal 1: (0,1), (1,0)
        // Diagonal 2: (0,2), (1,1), (2,0)
        // Diagonal 3: (1,2), (2,1)
        // Diagonal 4: (2,2)
        
        // Loop through each diagonal (identified by the sum of its indices)
        for (int diagonalIndex = 0; diagonalIndex < numRows + numCols - 1; diagonalIndex++) {
            
            // For each diagonal, we need to determine:
            // 1. The starting position
            // 2. The direction of traversal
            
            // Even-indexed diagonals go upward (↗): decreasing row, increasing column
            if (diagonalIndex % 2 == 0) {
                // For upward diagonals, we need to find the lowest possible 
                // starting point on this diagonal
                
                // First, we try to start as far down as possible
                int startRow = min(diagonalIndex, numRows - 1);
                
                // Calculate corresponding column
                // Since row + col = diagonalIndex, we have: col = diagonalIndex - row
                int startCol = diagonalIndex - startRow;
                
                // Now traverse the diagonal upward-right
                int currentRow = startRow;
                int currentCol = startCol;
                
                // Continue as long as we're within matrix boundaries
                while (currentRow >= 0 && currentCol < numCols) {
                    traversalResult.push_back(matrix[currentRow][currentCol]);
                    // Move diagonally up-right
                    currentRow--;
                    currentCol++;
                }
            }
            // Odd-indexed diagonals go downward (↙): increasing row, decreasing column
            else {
                // For downward diagonals, we need to find the rightmost possible
                // starting point on this diagonal
                
                // First, we try to start as far right as possible
                int startCol = min(diagonalIndex, numCols - 1);
                
                // Calculate corresponding row
                // Since row + col = diagonalIndex, we have: row = diagonalIndex - col
                int startRow = diagonalIndex - startCol;
                
                // Now traverse the diagonal downward-left
                int currentRow = startRow;
                int currentCol = startCol;
                
                // Continue as long as we're within matrix boundaries
                while (currentCol >= 0 && currentRow < numRows) {
                    traversalResult.push_back(matrix[currentRow][currentCol]);
                    // Move diagonally down-left
                    currentRow++;
                    currentCol--;
                }
            }
        }
        
        return traversalResult;
    }
