int height(TreeNode* root, int &diameter) {
    if (root == nullptr) return 0;
    
    int leftHeight = height(root->left, diameter);
    int rightHeight = height(root->right, diameter);
    
    // Update diameter if necessary
    auto currentDia = leftHeight + rightHeight + 1;
    diameter = max(diameter, currentDia);
    
    auto currentHeight = 1 + max(leftHeight, rightHeight)
    // Return the height of current node
    return currentHeight;
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

