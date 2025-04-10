
/*Converting a BST back to a Sorted Array
To convert a BST back to a sorted array, we use an inorder traversal of the BST. In a BST, an inorder traversal visits the nodes in ascending order of their values.

Perform an inorder traversal of the BST:
Recursively traverse the left subtree
Visit the root node (add its value to the result array)
Recursively traverse the right subtree
*/
// Function to create a BST from a sorted array
TreeNode* sortedArrayToBST(const std::vector<int>& nums, int start, int end) {
    // Base case: if the subarray is empty
    if (start > end) {
        return nullptr;
    }
    
    // Find the middle element
    int mid = start + (end - start) / 2;
    
    // Create the root node with the middle element
    TreeNode* root = new TreeNode(nums[mid]);
    
    // Recursively build the left subtree from the left half of the array
    root->left = sortedArrayToBST(nums, start, mid - 1);
    
    // Recursively build the right subtree from the right half of the array
    root->right = sortedArrayToBST(nums, mid + 1, end);
    
    return root;
}

// Wrapper function to simplify the API
TreeNode* sortedArrayToBST(const std::vector<int>& nums) {
    return sortedArrayToBST(nums, 0, nums.size() - 1);
}


/*
The Algorithm:
1. Take the first element of the pre-order traversal as the current root.
2. Find this element's position in the in-order traversal.
3. Elements to the left of this position in the in-order traversal form the left subtree.
4. Elements to the right of this position in the in-order traversal form the right subtree.
5. Recursively build the left and right subtrees using the appropriate subarrays of the pre-order and in-order traversals.

Time and Space Complexity:
Time Complexity: O(n), where n is the number of nodes in the tree. We build a hash map for O(n) lookup time, and process each node exactly once.
Space Complexity: O(n) for the recursion stack and the hash map.
Key Implementation Details:
We use a hash map to store the indices of elements in the in-order traversal for O(1) lookup.
The recursive function takes segments of both arrays defined by start and end indices.
For each recursive call, we calculate the size of the left subtree to determine the appropriate subarrays for further recursion.
*/

// Function to build binary tree from preorder and inorder traversal
TreeNode* buildTree(const std::vector<int>& preorder, const std::vector<int>& inorder, 
                   int preStart, int preEnd, int inStart, int inEnd,
                   std::unordered_map<int, int>& inorderMap) {
    
    if (preStart > preEnd || inStart > inEnd) {
        return nullptr;
    }
    
    // The first element in preorder traversal is the root
    TreeNode* root = new TreeNode(preorder[preStart]);
    
    // Find the position of the root in inorder traversal
    int inRootPos = inorderMap[root->val];
    
    // Calculate number of elements in left subtree
    int leftSubtreeSize = inRootPos - inStart;
    
    // Build left and right subtrees recursively
    // Left subtree elements in preorder: [preStart+1, preStart+leftSubtreeSize]
    // Left subtree elements in inorder: [inStart, inRootPos-1]
    root->left = buildTree(preorder, inorder, 
                        preStart + 1, preStart + leftSubtreeSize,
                        inStart, inRootPos - 1, inorderMap);
    
    // Right subtree elements in preorder: [preStart+leftSubtreeSize+1, preEnd]
    // Right subtree elements in inorder: [inRootPos+1, inEnd]
    root->right = buildTree(preorder, inorder,
                         preStart + leftSubtreeSize + 1, preEnd,
                         inRootPos + 1, inEnd, inorderMap);
    
    return root;
}

// Wrapper function to simplify the API
TreeNode* buildTree(const std::vector<int>& preorder, const std::vector<int>& inorder) {
    // Create a hashmap to quickly find the position of elements in inorder traversal
    std::unordered_map<int, int> inorderMap;
    for (int i = 0; i < inorder.size(); i++) {
        inorderMap[inorder[i]] = i;
    }
    
    return buildTree(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1, inorderMap);
}


