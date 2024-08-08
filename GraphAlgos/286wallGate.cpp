// do the breadth first search from all the Gates 


class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        int m = rooms.size();
        if (m == 0) return;
        int n = rooms[0].size();
        
        queue<pair<int, int>> q;
        vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        // Find all gates and add them to the queue
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (rooms[i][j] == 0) {
                    q.push({i, j});
                }
            }
        }
        
        // BFS from all gates simultaneously
        while (!q.empty()) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();
            
            for (auto dir : dirs) {
                int nx = x + dir.first;
                int ny = y + dir.second;
                
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && rooms[nx][ny] == INT_MAX) {
                    rooms[nx][ny] = rooms[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }
};