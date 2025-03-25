int rob_recursive_helper(vector<int>& nums, int index) {
    // Base cases
    if (index < 0) return 0;
    if (index == 0) return nums[0];
    
    // Two choices at each step:
    // 1. Rob current house and skip previous adjacent house
    // 2. Skip current house and take max from previous house
    return max(
        nums[index] + rob_recursive_helper(nums, index - 2),
        rob_recursive_helper(nums, index - 1)
    );
}

int rob_memo_helper(vector<int>& nums, int index, vector<int>& memo) {
        // Base cases
        if (index < 0) return 0;
        if (index == 0) return nums[0];
        
        // Return memoized result if already computed
        if (memo[index] != -1) return memo[index];
        
        // Compute and memoize result
        memo[index] = max(
            nums[index] + rob_memo_helper(nums, index - 2, memo),
            rob_memo_helper(nums, index - 1, memo)
        );
        
        return memo[index];
    }

     int rob_tabulation(vector<int>& nums) {
        // Handle edge cases
        if (nums.empty()) return 0;
        if (nums.size() == 1) return nums[0];
        
        // DP table to store maximum robbery amount up to each house
        vector<int> dp(nums.size());
        
        // Base cases
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        
        // Build solution bottom-up
        for (int i = 2; i < nums.size(); i++) {
            // Max of:
            // 1. Current house + max from two houses before
            // 2. Max from previous house (skip current)
            dp[i] = max(nums[i] + dp[i-2], dp[i-1]);
        }
        
        // Return maximum amount that can be robbed
        return dp.back();
    }

    // 5. RECONSTRUCT ROBBERY PATH
    vector<int> rob_with_path(vector<int>& nums) {
        if (nums.empty()) return {};
        if (nums.size() == 1) return {0};  // First house index
        
        // DP table and path tracking
        vector<int> dp(nums.size());
        vector<bool> rob_house(nums.size(), false);
        
        // Base cases
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        rob_house[0] = nums[0] > nums[1] ? true : false;
        
        // Build solution with path tracking
        for (int i = 2; i < nums.size(); i++) {
            if (nums[i] + dp[i-2] > dp[i-1]) {
                dp[i] = nums[i] + dp[i-2];
                rob_house[i] = true;
            } else {
                dp[i] = dp[i-1];
                rob_house[i] = false;
            }
        }
        
        // Reconstruct robbery path
        vector<int> robbery_path;
        int i = nums.size() - 1;
        while (i >= 0) {
            if (rob_house[i]) {
                robbery_path.push_back(i);
                i -= 2;  // Skip adjacent house
            } else {
                i--;
            }
        }
        
        return robbery_path;
    }