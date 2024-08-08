class Solution {
public:
    long long countWays(int n, int k) {
        // dp[i] represents the number of ways to paint i posts
        vector<long long> dp(n + 1, 0);
        
        const int MOD = 1e9 + 7;  // Change this to int
        
        // Base cases
        if (n == 0) return 0;
        if (n == 1) return k;
        
        // One post can be painted in k ways
        dp[1] = k;
        // Two posts can be painted in k * k ways
        dp[2] = static_cast<long long>(k) * k % MOD;
        
        // For 3 posts onwards
        for (int i = 3; i <= n; i++) {
            dp[i] = ((k - 1) * (dp[i-1] + dp[i-2])) % MOD;
        }
        
        return dp[n];
    }
};