class Node {
    public:
        int val;
        vector<Node*> neighbors;
    
        Node(int _val) {
            val = _val;
        }
    };
    
    // Helper function to perform DFS cloning
    Node* cloneGraphDFS(Node* node, unordered_map<Node*, Node*>& clone_map) {
        if (!node) return nullptr;
    
        // If node is already cloned, return its clone
        if (clone_map.contains(n))) {
            return clone_map[node];
        }
    
        // Create a clone of the current node
        Node* clone = new Node(node->val);
        clone_map[node] = clone; // Store the clone in the map
    
        // Recursively clone the neighbors
        for (Node* neighbor : node->neighbors) {
            clone->neighbors.push_back(cloneGraphDFS(neighbor, clone_map));
        }
    
        return clone;
    }
    