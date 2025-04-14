/**
top: the top-most row we haven't fully processed
right: the right-most column we haven't fully processed
bottom: the bottom-most row we haven't fully processed
left: the left-most column we haven't fully processed
As we traverse, we'll update these boundaries to move inward.

Algorithm
Initialize boundaries: top = 0, right = cols-1, bottom = rows-1, left = 0
While top <= bottom AND left <= right:
Traverse top row from left to right (increment top)
Traverse right column from top to bottom (decrement right)
If top <= bottom: Traverse bottom row from right to left (decrement bottom)
If left <= right: Traverse left column from bottom to top (increment left)
  */

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        // Handle empty matrix case
        if (matrix.empty()) {
            return {};
        }
        
        vector<int> result;
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        // Initialize boundaries
        int top = 0, right = cols - 1;
        int bottom = rows - 1, left = 0;
        
        while (top <= bottom && left <= right) {
            // Traverse from left to right along the top row
            for (int col = left; col <= right; col++) {
                result.push_back(matrix[top][col]);
            }
            top++;
            
            // Traverse from top to bottom along the rightmost column
            for (int row = top; row <= bottom; row++) {
                result.push_back(matrix[row][right]);
            }
            right--;
            
            // Traverse from right to left along the bottom row
            if (top <= bottom) {
                for (int col = right; col >= left; col--) {
                    result.push_back(matrix[bottom][col]);
                }
                bottom--;
            }
            
            // Traverse from bottom to top along the leftmost column
            if (left <= right) {
                for (int row = bottom; row >= top; row--) {
                    result.push_back(matrix[row][left]);
                }
                left++;
            }
        }
        
        return result;
    }
};
