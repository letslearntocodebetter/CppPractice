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


// A node being visited means we've completely explored it and all its dependencies.
// A node being inStack means we're currently exploring it and haven't finished checking all its dependencies yet.

// To detect a cycle, we need to know if we encounter a node that we're already in the process of exploring. That's what inStack tells us.
// Regarding your question about changing the order of checks, let's analyze:
// cppCopy// Current order
// if (inStack[course]) {
//     return false;  // Cycle detected
// }
// if (visited[course]) {
//     return true;  // Already processed this course
// If we reverse the order:
// if (visited[course]) {
//     return true;  // Already processed this course
// }
// if (inStack[course]) {
//     return false;  // Cycle detected
// }
// This would still work correctly because:

// If a node is already fully visited, we've previously determined it doesn't lead to cycles
// Once we're done processing a node, we set inStack[course] = false, so a fully visited node won't be in the stack

// However, checking inStack first is slightly more efficient in cases where there's a cycle, as we can fail fast without needing to check visited.
// This approach using both arrays is called the "white-gray-black" DFS algorithm for cycle detection:

// White: Unvisited nodes (!visited[node] and !inStack[node])
// Gray: Nodes being processed (visited[node] and inStack[node])
// Black: Fully processed nodes (visited[node] and !inStack[node]) O(V+E) time and space both

A cycle exists if and only if we encounter a gray node during traversal.RetryClaude does not have the ability to run the code it generates yet.Claude can make mistakes. Please double-check responses.


}
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
        result.push_back(node);  // Add to result on backtrack (post-order)
        return true;
    }

// result.rever()
   0
  / \
 1   2
  \ /
   3




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
            if (!visited[i]) {
                if (!dfs(i, graph, visited, inStack)) {
                    return false;
                }
            }
        }
        
        return true;
    }
};


/*
🔁 DFS Post-order Traversal Flow
Let's trace what happens if we start DFS from node 0:

DFS(0)
    → DFS(1)

        → DFS(3)

            3 has no outgoing edges → Add 3 to result

    Add 1 to result

    → DFS(2)

        → DFS(3) already visited → skip

    Add 2 to result

Add 0 to result

✅ Result (before reversing):
csharp
Copy
Edit
[3, 1, 2, 0]
*/

// Kahn topological sort

class Solution {

    /**
     * @brief Determines if it's possible to finish all courses given their prerequisites.
     *
     * This function uses Kahn's algorithm for topological sorting to check if there
     * are any cycles in the course dependency graph. If all courses can be completed,
     * it returns true; otherwise, it returns false.
     *
     * @param numCourses The total number of courses.
     * @param prerequisites A vector of vectors where each inner vector represents a prerequisite relationship.
     *                      prerequisites[i] = [a, b] means course 'b' must be taken before course 'a'.
     * @return bool Returns true if it's possible to finish all courses, false otherwise.
     */
    bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        std::vector<std::vector<int>> graph(numCourses);
        std::vector<int> inDegree(numCourses, 0);
    
        // Build the graph and compute in-degrees
        for (auto& pre : prerequisites) {
            graph[pre[1]].push_back(pre[0]);
            inDegree[pre[0]]++;
        }
        
          vector<int> order;
        // Push all nodes with in-degree 0 into the queue
        std::queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) q.push(i);
        }
    
        int count = 0;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            order.push_back(course);
            count++;
    
            for (int neighbor : graph[course]) {
                if (--inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
    
        return count == numCourses;
    }
    
};
