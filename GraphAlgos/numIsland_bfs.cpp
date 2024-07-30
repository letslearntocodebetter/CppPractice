class Solution {
public:
    bool bounded(int x, int y, const vector<vector<char>>& grid) {
       return x >= 0 && x < grid.size() &&
              y >= 0 && y < grid[0].size();
    }
    void dfs(int i, int j, const vector<vector<char>>& grid, 
vector<vector<bool>>& visited)
{
    if (!bounded(i, j, grid) || visited[i][j] || grid[i][j] == '0') {
        return;
    }
    visited[i][j] = true;
    const vector<pair<int,int>> dir = {{1,0},{0,1},{-1,0},{0,-1}};
    for (const auto &[di, dj] : dir) {
        int nx = i + di;
        int ny = j + dj;
        dfs(nx, ny, grid, visited);
    }
}
    void bfs(int i, int j, const vector<vector<char>>& grid, 
    vector<vector<bool>>& visited)
    {
        queue<pair<int,int>> q{};
        q.push({i,j});
        const vector<pair<int,int>> dir = {{1,0},{0,1},{-1,0},{0,-1}};
        while (!q.empty()) {
            const auto [x, y] = q.front();
            q.pop();
            for (const auto &[di, dj] : dir) {
                int nx = x + di;
                int ny = y + dj;
                if (bounded(nx, ny, grid) && !visited[nx][ny] && grid[nx][ny] == '1') {
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
    }
    
    int numIslands(vector<vector<char>>& grid)
    {
        if (grid.empty()) {
            return 0;
        }
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int count = 0;
    
        for (int i = 0; i < m ; i++) {
            for (int j = 0; j < n; j++) {
                if (!visited[i][j] && grid[i][j] == '1') {
                    count++;
                    bfs(i, j , grid, visited);
                }
            }
        }
        return count;
    }
};