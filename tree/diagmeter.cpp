int height(TreeNode* root, int &diameter) {
    if (root == nullptr) return 0;
    
    int leftHeight = height(root->left, diameter);
    int rightHeight = height(root->right, diameter);
    
    // Update diameter if necessary
    diameter = max(diameter, leftHeight + rightHeight);
    
    // Return the height of current node
    return 1 + max(leftHeight, rightHeight);
}