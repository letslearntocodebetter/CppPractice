// visit the island and use the grid itself to mark them as visited by putting the value as 0
// and then see how many such travels  can be done


#include <vector>
using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;

        int numIslands = 0;
        int rows = grid.size();
        int cols = grid[0].size();

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == '1') {
                    ++numIslands;
                    dfs(grid, r, c);
                }
            }
        }
        return numIslands;
    }

private:
    void dfs(vector<vector<char>>& grid, int r, int c) {
        int rows = grid.size();
        int cols = grid[0].size();
        
        if (r < 0 || c < 0 || r >= rows || c >= cols || grid[r][c] == '0') {
            return;
        }

        grid[r][c] = '0'; // Mark as visited

        dfs(grid, r - 1, c); // Up
        dfs(grid, r + 1, c); // Down
        dfs(grid, r, c - 1); // Left
        dfs(grid, r, c + 1); // Right
    }
};

// alternate solution
void dfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int i, int j) {
    if (!isValid(i, j, grid) || visited[i][j] || grid[i][j] == '0') {
        return;
    }

    visited[i][j] = true;
    grid[i][j] = '0';

    vector<pair<int, int>> neighbors{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    for (auto& [dx, dy] : neighbors) {
        int x = i + dx;
        int y = j + dy;
        dfs(grid, visited, x, y);
    }
}



void bfs(std::vector<std::vector<char>>& grid, std::vector<std::vector<bool>>& visited, int startRow, int startCol) {
        std::queue<std::pair<int, int>> q;
        q.push({startRow, startCol});
        visited[startRow][startCol] = true;

        while (!q.empty()) {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();

            std::vector<std::pair<int, int>> neighbors{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
            for (auto& neighbor : neighbors) {
                int newRow = row + neighbor.first;
                int newCol = col + neighbor.second;

                if (isValid() &&
                    grid[newRow][newCol] == '1' && !visited[newRow][newCol]) {
                    q.push({newRow, newCol});
                    visited[newRow][newCol] = true;
                }
            }
        }
    }