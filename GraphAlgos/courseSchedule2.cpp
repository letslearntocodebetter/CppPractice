// same as courseSchedule1 
// in addition we maintane a result list where the order in which DFS is done gets stored in a vector


class Solution {
private:
    bool dfs(int course, vector<vector<int>>& graph, vector<bool>& visited, vector<bool>& inStack, vector<int>& order) {
        if (inStack[course]) return false;  // Cycle detected
        if (visited[course]) return true;   // Already processed

        visited[course] = true;
        inStack[course] = true;

        for (int neighbor : graph[course]) {
            if (!dfs(neighbor, graph, visited, inStack, order)) {
                return false;
            }
        }

        inStack[course] = false;
        order.push_back(course);  // Add course to order after processing all prerequisites
        return true;
    }

public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        
        // Build the graph
        for (const auto& prereq : prerequisites) {
            graph[prereq[0]].push_back(prereq[1]);
        }

        vector<bool> visited(numCourses, false);
        vector<bool> inStack(numCourses, false);
        vector<int> order;

        // Perform DFS for each course
        for (int i = 0; i < numCourses; i++) {
            if (!dfs(i, graph, visited, inStack, order)) {
                return {};  // Return empty array if cycle is detected
            }
        }

        return order;  // Return the order of courses
    }
};