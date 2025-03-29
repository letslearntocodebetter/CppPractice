
// Helper function to find all paths that sum to target
/**
 * @brief Helper function to find all paths that sum to target in a binary tree.
 *
 * This function uses a depth-first search approach to traverse the binary tree.
 * It keeps track of the current path and the remaining sum to reach the target.
 * When a leaf node is reached and the remaining sum is zero, the current path is added to the result.
 *
 * @param root The root node of the binary tree.
 * @param targetSum The target sum to find in the paths.
 * @param currentPath The current path being explored.
 * @param resultPaths The collection of all paths that sum to the target.
 *
 * @return void
 */
void findAllPaths(TreeNode* root, int targetSum, vector<int>& currentPath, vector<vector<int>>& resultPaths) {
    if (!root) {
        return; // If node is null, simply return
    }

    // Add the current node to the path
    currentPath.push_back(root->val);

    // If it's a leaf node and the target sum is reached, add the path to the result
    if (!root->left && !root->right && root->val == targetSum) {
        resultPaths.push_back(currentPath); // Store the current valid path
    } else {
        // Continue searching in the left and right subtrees
        int remainingSum = targetSum - root->val;
        findAllPaths(root->left, remainingSum, currentPath, resultPaths);
        findAllPaths(root->right, remainingSum, currentPath, resultPaths);
    }

    // Backtrack: remove the current node from the path if no valid path was found
    currentPath.pop_back();
}
