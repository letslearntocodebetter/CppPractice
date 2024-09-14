Summary: BFS vs. DFS Marking Visited Nodes
BFS: Nodes are marked as visited before enqueueing them to the queue.
This is because BFS explores nodes layer-by-layer, and marking 
upon enqueueing avoids revisiting nodes while still 
maintaining the shortest path exploration in an unweighted graph.

DFS: Nodes are marked as visited upon processing (i.e., when popped from the stack). 
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

dfs(int node, std::unorded_map<int, vector<int>>&graph, std::vector<bool>& visited) {
    std::stack<int> stack{};
    stack.push(node);

    while(!stack.empty()) {
        auto node = stack.top();
        visite[node] = true;
        stack.pop();
        for(auto neigh : graph[node]) {
            if (!visited[neigh]) {
                stack.push(neigh);
            }
        }

    }
}

BFS(int start, graph, visited) {

    queue q;
    q.push(start);
    visited[strart] = true;

    while (!q.empty()) {
        auto node =  q.front();
        q.pop();
        for (auto neigh : graph[node]) {
            if (!visited[neigh]) {
                visited[neigh] = true;
                BFS(neigh, graph, visited)
            }
        }

    }

}

void DFSOptimized(int s) {
    std::vector<bool> visited(V, false);
    std::stack<int> stack;

    stack.push(s);
    visited[s] = true;  // Mark as visited when pushing

    while (!stack.empty()) {
        s = stack.top();
        stack.pop();
        std::cout << s << " ";

        for (int adjacent : adj[s]) {
            if (!visited[adjacent]) {
                stack.push(adjacent);
                visited[adjacent] = true;  // Mark as visited when pushing
            }
        }
    }
}