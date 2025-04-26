/*
Approaching Vertical Order Traversal
Vertical order traversal is a fundamental concept that helps us understand both top view and bottom view operations. Let me explain my thought process and algorithm for vertical order traversal:
Chain of Thoughts for Vertical Order Traversal

Understanding Vertical Order:

We need to group nodes based on their horizontal distance (HD) from the root
Root has HD = 0
Left child of a node has HD = parent's HD - 1
Right child of a node has HD = parent's HD + 1
We want to print all nodes at each HD from leftmost to rightmost


Designing the Algorithm:

We need to track both horizontal distance and level for each node
We want to process nodes in a top-to-bottom, left-to-right manner
For this, level order traversal (BFS) is perfect
We'll use a map to group nodes by their HD
Within each HD, we'll maintain the order of nodes as they appear


Data Structures Needed:

A map where key = HD, value = list of node values at that HD
A queue for level order traversal that tracks node, HD, and level



Step-by-Step Algorithm

Create an empty map verticalOrder where key is horizontal distance and value is a list of node values
Create a queue for BFS and enqueue the root with HD = 0 and level = 0
While the queue is not empty:

Dequeue a node along with its HD and level
Add the node's value to the list at verticalOrder[HD]
Enqueue left child with HD-1 and level+1 (if exists)
Enqueue right child with HD+1 and level+1 (if exists)


Traverse the map in order of keys (HD) and print values

Now, let's implement this step by step:
Chain of Thoughts for Top View

Understanding Top View:

Top view contains nodes that would be visible when looking at the tree from above
For each horizontal distance, we need only the first (top-most) node
If two nodes share the same HD, the one with smaller level value is in the top view
If two nodes have the same HD and level, the earlier one in traversal order is chosen


From Vertical Order to Top View:

We again group nodes by HD in vertical order traversal
For top view, we take the first node at each HD
Using level order with a conditional insert ensures we only record the first node at each HD



Bottom View Algorithm

Create an empty map bottomView where key is HD and value is node value
Perform level order traversal with HD tracking
For each node encountered, update bottomView[HD] with its value
After traversal, the map contains the bottom-most nodes at each HD
Print the values from the map in order of keys (HD)

Top View Algorithm

Create an empty map topView where key is HD and value is node value
Perform level order traversal with HD tracking
For each node, if topView[HD] doesn't exist, add the node's value
After traversal, the map contains the top-most nodes at each HD
Print the values from the map in order of keys (HD)

Now, let's implement both views based on our vertical order traversal approach:
cpp

*/

using Result = vector<vector<int>>;

Result verticalOrderTraversal(TreeNode* root) {
    Result reslut;
    if (!root) return;
    
    // Map: horizontal distance -> map of (level -> list of node values)
    // This ensures nodes are first grouped by HD, then sorted by level
    map<int, map<int, vector<int>>> verticalOrder;
    
    queue<tuple<TreeNode*, int, int>> q;
    q.push({root, 0, 0});
    
    while (!q.empty()) {
        auto [node, hd, level] = q.front();
        q.pop();
        
        // Group by both HD and level
        verticalOrder[hd][level].push_back(node->val);
        
        if (node->left) {
            q.push({node->left, hd-1, level+1});
        }
        
        if (node->right) {
            q.push({node->right, hd+1, level+1});
        }
    }
    
    Result // Print vertical order traversal
    cout << "Vertical Order Traversal (sorted by level):" << endl;
    for (auto& [hd, levelMap] : verticalOrder) {
        cout << "HD " << hd << ": ";
        for (auto& [level, values] : levelMap) {
            // Optionally sort values at same level and HD
            sort(values.begin(), values.end());
             result.push_back(values) 
        }
        cout << endl;
    }
}



// Function for bottom view
void bottomView(TreeNode* root) {
    if (!root) return;
    
    // Map to store the last node at each horizontal distance
    map<int, int> bottomNodes;
    
    // Queue for level order traversal
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});  // Root has HD = 0
    
    while (!q.empty()) {
        TreeNode* node = q.front().first;
        int hd = q.front().second;
        q.pop();
        
        // Update the node at this HD (overwrites any previous node)
        bottomNodes[hd] = node->val;
        
        // Process children
        if (node->left) q.push({node->left, hd-1});
        if (node->right) q.push({node->right, hd+1});
    }
    
    // Print bottom view
    cout << "Bottom View: ";
    // they are alredy in the sorted oreded in the map
    for (auto& [hd, val] : bottomNodes) {
        cout << val << " ";
    }
    cout << endl;
}

// Function for top view
void topView(TreeNode* root) {
    if (!root) return;
    
    // Map to store the first node at each horizontal distance
    map<int, int> topNodes;
    
    // Queue for level order traversal
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});  // Root has HD = 0
    
    while (!q.empty()) {
        TreeNode* node = q.front().first;
        int hd = q.front().second;
        q.pop();
        
        // Add this node only if this HD hasn't been seen before
        if (topNodes.find(hd) == topNodes.end()) {
            // only care abou the first insert ,  ignore the duplicate second one
            topNodes[hd] = node->val;
        }
        
        // Process children
        if (node->left) q.push({node->left, hd-1});
        if (node->right) q.push({node->right, hd+1});
    }
    
    // Print top view
    cout << "Top View: ";
    for (auto& [hd, val] : topNodes) {
        cout << val << " ";
    }
    cout << endl;
}
