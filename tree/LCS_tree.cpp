  // The LCS is the lowest node where both p and q are location in left and right side.
  // if both are on sane side then go deepr



        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
            // Base case: If root is null or root is one of p or q
            if (!root || root == p || root == q) {
                return root;
            }
            
            // If both p and q are smaller than root, move to the left subtree
            if (p->val < root->val && q->val < root->val) {
                return lowestCommonAncestor(root->left, p, q);
            }
            
            // If both p and q are greater than root, move to the right subtree
            if (p->val > root->val && q->val > root->val) {
                return lowestCommonAncestor(root->right, p, q);
            }
            
            // If p and q are on different sides, return the current node as LCA
            return root;
        }



        TreeNode* lowestCommonAncestor_Iterative(TreeNode* root, TreeNode* p, TreeNode* q) {
        while (root) {
            // If both p and q are smaller than root, move to the left subtree
            if (p->val < root->val && q->val < root->val) {
                root = root->left;
            }
            // If both p and q are greater than root, move to the right subtree
            else if (p->val > root->val && q->val > root->val) {
                root = root->right;
            }
            // If p and q are on different sides, root is the LCA
            else {
                return root;
            }
        }
        return nullptr;  // This should never be hit because one of p or q should exist in the tree