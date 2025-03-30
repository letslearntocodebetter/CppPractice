#include <bits/stdc++.h>

class Solution {
    public:
        vector<int> rightSideView(TreeNode* root) {
            if (root == nullptr) {
                return {};
            }
    
            vector<int> rightSideView;
            std::queue<TreeNode*> nodeQueue;  // Renamed q to nodeQueue for clarity
            nodeQueue.push(root);
    
            while (!nodeQueue.empty()) {
                int levelSize = nodeQueue.size();  // Renamed curSize to levelSize
                
                for (int i = 0; i < levelSize; ++i) {
                    auto* node = nodeQueue.front();
                    nodeQueue.pop();
    
                    // Only push the rightmost node at each level
                    if (i == levelSize - 1) {
                        rightSideView.push_back(node->val);
                    }
    
                    // Push left and right children of the current node
                    if (node->left) {
                        nodeQueue.push(node->left);
                    }
                    if (node->right) {
                        nodeQueue.push(node->right);
                    }
                }
            }
    
            return rightSideView;
        }
    };
    