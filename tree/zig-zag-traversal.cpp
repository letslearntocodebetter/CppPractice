// we can use deque and then push pop_front or pop_back depening upone the leftToWrite Flag.
// But we must alway enaueue using push_back same as std::queue.

 // Alternative implementation using deque for more modern C++ approach
    static std::vector<std::vector<int>> zigzagLevelOrderUsingDeque(TreeNode* root) {
        if (!root) return {};
        
        std::vector<std::vector<int>> result;
        std::deque<TreeNode*> dq;
        dq.push_back(root);
        
        // Flag to track direction
        bool leftToRight = true;
        
        while (!dq.empty()) {
            int levelSize = dq.size();
            std::vector<int> currentLevel;
            currentLevel.reserve(levelSize);
            
            // Process current level
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* node;
                
                if (leftToRight) {
                    // Process from front
                    node = dq.front();
                    dq.pop_front();
                    
                    // Add children (always left then right)
                    if (node->left) dq.push_back(node->left);
                    if (node->right) dq.push_back(node->right);
                } else {
                    // Process from back
                    node = dq.back();
                    dq.pop_back();
                    
                    // Add children in reverse order (right then left)
                    // and to the front to maintain the desired traversal
                    if (node->right) dq.push_front(node->right);
                    if (node->left) dq.push_front(node->left);
                }
                
                currentLevel.push_back(node->val);
            }
            
            result.push_back(std::move(currentLevel));
            leftToRight = !leftToRight;
        }
        
        return result;
    }

class Solution {
public:
    std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root) {
        // Handle edge case of empty tree
        if (!root) {
            return {};
        }
        
        std::vector<std::vector<int>> result;
        std::queue<TreeNode*> q;
        q.push(root);
        
        // Initialize direction flag (true for left-to-right, false for right-to-left)
        bool leftToRight = true;
        
        while (!q.empty()) {
            int levelSize = q.size();
            
            // Pre-allocate vector for current level with correct size
            std::vector<int> currentLevel(levelSize);
            
            for (int i = 0; i < levelSize; ++i) {
                // Get current node
                TreeNode* node = q.front();
                q.pop();
                
                // Calculate index based on current direction
                int index = leftToRight ? i : levelSize - 1 - i;
                
                // Store value at calculated index
                currentLevel[index] = node->val;
                
                // Add children to queue for next level processing
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            
            // Add current level to result
            result.push_back(std::move(currentLevel));
            
            // Toggle direction for next level
            leftToRight = !leftToRight;
        }
        
        return result;
    }
};


