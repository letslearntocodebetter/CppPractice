/**
The chain of returns is crucial:
Each deletion function returns the new root of its modified subtree
Each parent uses this return value to update its connections
By returning the root at each level, we maintain a properly connected tree
Without returning the root and assigning it to the appropriate child pointer, we would lose parts of the tree structure when nodes are deleted or replaced.
*/

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // Helper function to find the minimum value node in the subtree
// 
    TreeNode* findInorderSucccessor(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return nullptr;

        // Traverse the tree to find the node to delete
        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else {
            // Node found

            // Case 1: No left child
            if (!root->left) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            }
            // Case 2: No right child
            else if (!root->right) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }
            // Case 3: Two children
            else {
                TreeNode* successor = findInOrderSuccessor(root->right);
                root->val = successor->val;
                root->right = deleteNode(root->right, successor->val);
            }
        }
        return root;
    }
};
