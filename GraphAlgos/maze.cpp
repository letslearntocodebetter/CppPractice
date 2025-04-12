/*
Ball Rolling Logic: The most critical fix is correctly implementing how the ball rolls. 
In this problem, the ball keeps moving in one direction until it hits a wall, not just one step at a time.
Visited State: We only mark a position as visited after the ball stops rolling, not at every cell it passes through.
Boundary Checking: Added proper checking to ensure the ball stays within the maze.
Function Completion: Completed the hasPath function to actually call the DFS function.
Parameter Passing: Changed to pass row and column as integers rather than a vector for efficiency.
*/


class Solution {
    private:
        static constexpr std::array<std::pair<int, int>, 4> dir = {{{0, 1}, {0, -1}, {-1, 0}, {1, 0}}};
        
        bool dfs(vector<vector<int>>& maze, vector<vector<bool>>& visited, 
                 int i, int j, vector<int>& dest) {
            
            // If already visited, no need to explore
            if (visited[i][j]) return false;
            
            // If destination reached, return true
            if (i == dest[0] && j == dest[1]) return true;
            
            // Mark current position as visited
            visited[i][j] = true;
            
            // Try each direction
            for (auto [dx, dy] : dir) {
                int x = i, y = j;
                
                // Roll the ball until hitting a wall
                do {
                    x += dx;
                    y += dy;
                } while (x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size() && maze[x][y] == 0);
                
                // Move back one step (we hit a wall or boundary)
                x -= dx;
                y -= dy;
                
                // Only explore if we actually moved and the new position is not visited
                if ((x != i || y != j) && !visited[x][y]) {
                    if (dfs(maze, visited, x, y, dest)) {
                        return true;
                    }
                }
            }
            
            return false;
        }
        
    public:
        bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
            int m = maze.size(), n = maze[0].size();
            vector<vector<bool>> visited(m, vector<bool>(n, false));
            
            return dfs(maze, visited, start[0], start[1], destination);
        }
    };


    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        if (maze.empty() || maze[0].empty()) return false;
        int m = maze.size(), n = maze[0].size();
        
        // Create visited matrix
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        
        // Directions: up, right, down, left
        vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        
        // Stack for DFS
        stack<pair<int, int>> st;
        st.push({start[0], start[1]});
        visited[start[0]] [start[1]] = true;

        while (!st.empty())
        {
            auto [curX, curY] = st.top();
            st.pop();

            // find the next position to explore
            int x = curX;
            int y = curY;

            for(auto &[dx, dy] : directions)
            {
                do
                {
                    x += dx;
                    y += dy;
                } while (x >= 0 && y >= 0 && x < m & y < n && maze[x][y] == 0);
                // come back one step
                x -= dx;
                y -= dy;
                if (x != curX || y != curY)
                {
                    if (x == destination[0] && y == destination[1])
                        return true;
                    if (!visited[x][y])
                    {
                        visited[x][y] = true;
                        st.push({x, y});
                    }
                }
            }
        }
}
bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    if (maze.empty() || maze[0].empty()) return false;
    int m = maze.size(), n = maze[0].size();
    
    // Create visited matrix
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    
    // Directions: up, right, down, left
    vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    
    // Stack for DFS
    stack<pair<int, int>> st;
    st.push({start[0], start[1]});
    visited[start[0]][start[1]] = true;
    
    while (!st.empty()) {
        auto [curX, curY] = st.top();
        st.pop();
        
        // Check if reached destination
        if (curX == destination[0] && curY == destination[1]) 
            return true;
        
        // Try each direction
        for (auto& [dx, dy] : directions) {
            int x = curX, y = curY;  // Reset x and y for each new direction
            
            // Roll the ball until hitting a wall
            while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0) {
                x += dx;
                y += dy;
            }
            
            // Move back one step
            x -= dx;
            y -= dy;
            
            // Only explore if we actually moved and haven't visited this position
            if ((x != curX || y != curY) && !visited[x][y]) {
                visited[x][y] = true;
                st.push({x, y});
            }
        }
    }
    
    return false;  // Return false if destination not reachable
}