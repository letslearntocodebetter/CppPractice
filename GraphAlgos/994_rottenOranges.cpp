
// it is like a level order tranversal with all rotten co-ordinate in the queue
// then level order tranversal 
// if we cannot access all fruits then some would remain ripe
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int, int>> q;
        int fresh = 0;
        int time = 0;
        
        // Step 1: Count fresh oranges and add rotten oranges to the queue
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    fresh++;
                } else if (grid[i][j] == 2) {
                    q.push({i, j});
                }
            }
        }
        
        // Directions: up, down, left, right
        const vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        // Step 2: BFS
        while (!q.empty() && fresh > 0) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto [x, y] = q.front();
                q.pop();
                
                for (auto dir : dirs) {
                    auto [nx, ny] = {dir.first +x , dir.second +y};

                    if (isBounded(nx, ny, grid) && grid[nx][ny] == 1) {
                        grid[nx][ny] = 2;
                        fresh--;
                        q.push({nx, ny});
                    }
                }
            }
            time++;
        }
        
        // Step 3: Check if all oranges are
        return fresh == 0 ? time : -1;
    }
    bool isBounded(int nx, int ny, vector<vector<int>>grid) {
        return true;
    }
};


