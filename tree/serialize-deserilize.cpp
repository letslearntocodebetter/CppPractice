/*
Serialization Strategy:

We need to capture the tree structure including null nodes
I'll use a preorder traversal (root → left → right) to visit all nodes
We can separate values with a delimiter like commas
For null nodes, I'll use a special marker like "X"


Deserialization Strategy:

We'll parse the string to get individual node values
Since we used preorder traversal for serialization, we'll reconstruct in the same order
When we encounter a null marker ("X"), we'll return null
We need to track our position in the string as we rebuild the tree recursively
*/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

 class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) return "X,"; // Base case: null node represented as X
        
        // Use preorder traversal (root → left → right)
        // Convert current node value to string + recurse on left and right subtrees
        return to_string(root->val) + "," + 
               serialize(root->left) + 
               serialize(root->right);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        // Convert the string to a list for easier manipulation
        vector<string> nodes;
        
        string token;
        // Split the serialized string by comma delimiter
        for (char c : data) {
            if (c == ',') {
                nodes.push_back(token);
                token = "";
            } else {
                token += c;
            }
        }
        
        // Add the last token if it exists
        if (!token.empty()) {
            nodes.push_back(token);
        }
        
        // Initialize index to track our position in the list
        int index = 0;
        
        // Start the recursive deserialize process
        return buildTree(nodes, index);
    }

private:
    // Helper function to rebuild the tree recursively
    TreeNode* buildTree(vector<string>& nodes, int& index) {
        // Get the current node value
        string val = nodes[index++];
        
        // If it's a null marker, return null
        if (val == "X") {
            return nullptr;
        }
        
        // Create a new node with the current value
        TreeNode* node = new TreeNode(stoi(val));
        
        // Recursively build left and right subtrees
        // The index is passed by reference to keep track of our position
        node->left = buildTree(nodes, index);
        node->right = buildTree(nodes, index);
        
        return node;
    }
};

