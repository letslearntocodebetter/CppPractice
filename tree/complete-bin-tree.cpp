/**
The key insight is that in a complete binary tree, nodes should be filled in a level-order fashion from left to right with no gaps. We can use a level-order traversal (BFS) to check this:
Use a queue to perform level-order traversal
Once we encounter a null node, all subsequent nodes must also be null
If we find a non-null node after a null node, the tree is not complete
 */
class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        // Edge case: empty tree is complete
        if (!root) return true;
        
        // Use a queue for level-order traversal
        queue<TreeNode*> q;
        q.push(root);
        
        // Flag to track if we've seen a null node
        bool seenNull = false;
        
        // Level-order traversal
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            
            // Current node is null
            if (!current) {
                seenNull = true;
            } 
            // Current node is not null
            else {
                // If we've already seen a null node, tree is not complete
                if (seenNull) {
                    return false;
                }
                
                // Add left and right children (including nulls)
                q.push(current->left);
                q.push(current->right);
            }
        }
        
        // If we've reached here, the tree is complete
        return true;
    }
};


/*
DFS Approach Logic
In a complete binary tree, we can number the nodes starting from 1 (root) in the same way as a binary heap:
Root is indexed at 1
For any node with index i:
Left child has index 2*i
Right child has index 2*i + 1
The key insight is that in a complete tree, these indices must be consecutive from 1 to n (where n is the number of nodes) with no gaps.

Implementation Strategy
Count the total number of nodes in the tree (size n)
Assign indices to nodes using heap-like numbering
Check if the maximum index equals the total number of nodes
*/

class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        // First, count total nodes
        int nodeCount = countNodes(root);
        
        // Then check if indices are consecutive from 1 to nodeCount
        return isComplete(root, 1, nodeCount);
    }
    
private:
    int countNodes(TreeNode* root) {
        if (!root) return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
    
    bool isComplete(TreeNode* root, int index, int nodeCount) {
        if (!root) return true;
        
        // If index exceeds nodeCount, tree cannot be complete
        if (index > nodeCount) return false;
        
        // Check left and right subtrees
        return isComplete(root->left, 2*index, nodeCount) &&
               isComplete(root->right, 2*index + 1, nodeCount);
    }
};


















