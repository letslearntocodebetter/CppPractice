int maxPathSumHelper(TreeNode* node, int& maxSum) {
    if (node == nullptr) {
        return 0; // Base case: empty tree has a sum of 0
    }

    // Recursively find the max path sums of the left and right subtrees
    int leftSum = std::max(0, maxPathSumHelper(node->left, maxSum)); //If the leftSum is negative, we take 0
    int rightSum = std::max(0, maxPathSumHelper(node->right, maxSum)); //If the rightSum is negative, we take 0

    // Return the maximum path sum that can be extended from the current node
    tmp = node->val + std::max(leftSum, rightSum);

    // Calculate the maximum path sum passing through the current node
    maxSum = std::max(maxSum, node->val + leftSum + rightSum);

    // Return the maximum path sum that can be extended from the current node
    return tmp;