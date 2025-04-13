TreeNode* buildTreeHelper(vector<int>& preorder, int& index) {
    // Check if we've reached the end of the array
    if (index >= preorder.size()) return nullptr;
    
    // Get current value
    int val = preorder[index++];
    
    // Null marker (often represented as a specific value like -1 or INT_MIN)
    if (val == INT_MIN) return nullptr;
    
    // Create new node
    TreeNode* root = new TreeNode(val);
    
    // Recursively build left and right subtrees
    // We pass index by reference so it's updated across all recursive calls
    root->left = buildTreeHelper(preorder, index);
    root->right = buildTreeHelper(preorder, index);
    
    return root;
}


-----


class SolutionWithInorder {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // Create a map to quickly find indices in inorder traversal
        unordered_map<int, int> inorderMap;
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }
        
        int preIndex = 0;
        return buildTreeHelper(preorder, inorderMap, preIndex, 0, inorder.size() - 1);
    }
    
private:
    TreeNode* buildTreeHelper(
        vector<int>& preorder, 
        unordered_map<int, int>& inorderMap,
        int& preIndex, 
        int inStart, 
        int inEnd
    ) {
        // Base case: no elements to construct the tree
        if (inStart > inEnd) return nullptr;
        
        // Pick current node from preorder traversal
        int rootVal = preorder[preIndex++];
        TreeNode* root = new TreeNode(rootVal);
        
        // Find the position of this node in inorder traversal
        int inIndex = inorderMap[rootVal];
        
        // Using index in inorder traversal, construct left and right subtrees
        // Elements before inIndex in inorder are in left subtree
        root->left = buildTreeHelper(preorder, inorderMap, preIndex, inStart, inIndex - 1);
        
        // Elements after inIndex in inorder are in right subtree
        root->right = buildTreeHelper(preorder, inorderMap, preIndex, inIndex + 1, inEnd);
        
        return root;
    }
};