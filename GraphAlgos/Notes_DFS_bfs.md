Summary: BFS vs. DFS Marking Visited Nodes
BFS: Nodes are marked as visited before enqueueing them to the queue.
This is because BFS explores nodes layer-by-layer, and marking 
upon enqueueing avoids revisiting nodes while still 
maintaining the shortest path exploration in an unweighted graph.

DFS: Nodes are marked as visited upon processing (i.e., when pushing into the stack or before calling recursive funtion). 
This ensures that DFS explores the complete depth of one path before attempting others
and avoids prematurely marking nodes that may never actually be visited.


/ Pseudocode
function dfs(node, graph, visited):
    visited[node] = true
    print "We have visited node", node
    for each neighbour in graph[node]:
        if not visited[neighbour]:
            dfs(neighbour, graph, visited)


dfs(int node, std::vector<vector<int>> &graph, std::vector<bool>& visited) {

    visited[node] = true;
    coust << "we have visited the node"

    for (auto neighbour : graph[node]) {
        if (!visted{neighbour}) {
            dfs(neighhour, graph, visited);
        }
    }

}

void BFS(int start, vector<vector<int>>& graph, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;  // Mark when enqueuing

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (auto neigh : graph[node]) {
            if (!visited[neigh]) {
                visited[neigh] = true;  // Mark before enqueuing
                q.push(neigh);  // Correct BFS behavior
            }
        }
    }
}

void DFS(int start, vector<vector<int>>& adj, vector<bool>& visited) {
    stack<int> stack;
    stack.push(start);
    visited[start] = true;

    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();
        cout << node << " ";

        for (int neighbor : adj[node]) {  // No need for reverse order
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                stack.push(neighbor);
            }
        }
    }
}

void DFS(int start, vector<vector<int>>& adj, vector<bool>& visited) {
    stack<int> stack;
    stack.push(start);
    visited[start] = true;

    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();
        cout << node << " ";

        for (int neighbor : adj[node]) {  // No need for reverse order
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                stack.push(neighbor);
            }
        }
    }
}
