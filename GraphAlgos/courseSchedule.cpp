// whihle we do dfs we can keep track if the node is visited again in the same level of depth
// the other way to figure out is only use visited

// if visited[coure] == 2 mean that we are revisiting the node and hence there is a cycle 
//
//

#include <vector>
#include <unordered_map>

class Solution {
private:
    bool dfs(int course, std::unordered_map<int, std::vector<int>>& graph, std::vector<bool>& visited, std::vector<bool>& inStack) {
        if (inStack[course]) {
            return false;  // Cycle detected
        }
        if (visited[course]) {
            return true;  // Already processed this course
        }
        
        visited[course] = true;
        inStack[course] = true;
        
        for (int neighbor : graph[course]) {
            if (!dfs(neighbor, graph, visited, inStack)) {
                return false;
            }
        }
        
        inStack[course] = false;
        return true;
    }

public:
    bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        std::unordered_map<int, std::vector<int>> graph;
        
        // Build the graph
        for (const auto& prereq : prerequisites) {
            graph[prereq[0]].push_back(prereq[1]);
        }
        
        std::vector<bool> visited(numCourses, false);
        std::vector<bool> inStack(numCourses, false);
        
        // Perform DFS for each course
        for (int i = 0; i < numCourses; i++) {
            if (!dfs(i, graph, visited, inStack)) {
                return false;
            }
        }
        
        return true;
    }
};