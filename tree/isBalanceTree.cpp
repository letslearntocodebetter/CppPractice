class Solution {
    public:
        int checkHeight(TreeNode *root, bool &isBalanced) {
            if (!root || !isBalanced) return 0;  // Early return if already unbalanced
    
            int leftHeight = checkHeight(root->left, isBalanced);
            int rightHeight = checkHeight(root->right, isBalanced);
    
            if (std::abs(leftHeight - rightHeight) > 1) {
                isBalanced = false;
                return 0; // No need to calculate further
            }
    
            return 1 + std::max(leftHeight, rightHeight);
        }
    
        bool isBalanced(TreeNode* root) {
            bool isBalanced = true;
            checkHeight(root, isBalanced);
            return isBalanced;
        }
    };
    