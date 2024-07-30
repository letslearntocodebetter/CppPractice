// same as the numIsland issue but the number
// the trick is first traverls and make all the edge cases as visite so that in
// in next parse we do not account those edge

#include <vector>
using namespace std;

class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        
        // Mark all '0's connected to the boundary as non-closed islands
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                
                // This is for the first edge case
                if ((r == 0 || r == rows - 1 || c == 0 || c == cols - 1) && grid[r][c] == 0) {
                    dfs(grid, r, c);
                }
            }
        }

        int closedIslands = 0;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 0) {
                    ++closedIslands;
                    dfs(grid, r, c);
                }
            }
        }
        return closedIslands;
    }

private:
    void dfs(vector<vector<int>>& grid, int r, int c) {
        int rows = grid.size();
        int cols = grid[0].size();
       
       // check the boundery conditons first
        if (r < 0 || c < 0 || r >= rows || c >= cols || grid[r][c] != 0) {
            return;
        }

        grid[r][c] = 1; // Mark as visited

       // visit the neighours

       static const vector<pair<int,int>> dir{{-1,0}, {1,0}, {0,1}, {0,-1}};
        for (auto [dx, dy] : dir) {
            int nx = i + dx;
            int ny = j + dy;
            dfs(grid, nx, ny);
        }
    }
};
