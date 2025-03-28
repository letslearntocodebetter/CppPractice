int height(TreeNode* root, int &diameter) {
    if (root == nullptr) return 0;
    
    int leftHeight = height(root->left, diameter);
    int rightHeight = height(root->right, diameter);
    
    // Update diameter if necessary
    diameter = max(diameter, leftHeight + rightHeight);
    
    // Return the height of current node
    return 1 + max(leftHeight, rightHeight);
}


int getDiameter(TreeNode* root, int &diameter) {
    if (!root) return 0;


    int leftDia = getDiameter(root->left, diagmerter);
    int rightDia = getDiagmeter(root->right, diameter);


    // if the node has to pass the diagmeter to the parent node
    int tmp = max(leftDia, rightDia) + 1;

    // if this node is the diameter then update it
    diameter = max(diameter, left + right + 1);

    return tmp;

}

