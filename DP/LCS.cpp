#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    // 1. RECURSIVE APPROACH
    // Time: O(2^(m+n)), Space: O(m+n) call stack
    int longestCommonSubsequence_recursive(string text1, string text2) {
        // Base case: if either string is empty
        if (text1.empty() || text2.empty()) 
            return 0;
        
        // If last characters match, include in subsequence
        if (text1.back() == text2.back()) {
            // Remove last character from both and add 1
            return 1 + longestCommonSubsequence_recursive(
                text1.substr(0, text1.length()-1), 
                text2.substr(0, text2.length()-1)
            );
        }
        
        // If last characters don't match, try two options
        return max(
            longestCommonSubsequence_recursive(text1.substr(0, text1.length()-1), text2),
            longestCommonSubsequence_recursive(text1, text2.substr(0, text2.length()-1))
        );
    }
    
    // 2. MEMOIZATION APPROACH
    // Time: O(m*n), Space: O(m*n)
    int longestCommonSubsequence_memoization(string text1, string text2) {
        // Create memoization vector to store computed results
        vector<vector<int>> memo(text1.length() + 1, 
                                  vector<int>(text2.length() + 1, -1));
        
        // Call helper function with initial parameters
        return memoHelper(text1, text2, text1.length(), text2.length(), memo);
    }
    
private:
    int memoHelper(const string& text1, const string& text2, 
                   int m, int n, vector<vector<int>>& memo) {
        // Base cases
        if (m == 0 || n == 0) return 0;
        
        // Check if result already computed
        if (memo[m][n] != -1) return memo[m][n];
        
        // If last characters match
        if (text1[m-1] == text2[n-1]) {
            memo[m][n] = 1 + memoHelper(text1, text2, m-1, n-1, memo);
            return memo[m][n];
        }
        
        // If last characters don't match
        memo[m][n] = max(
            memoHelper(text1, text2, m-1, n, memo),
            memoHelper(text1, text2, m, n-1, memo)
        );
        
        return memo[m][n];
    }

public:
    // 3. TABULATION (TOP-DOWN) APPROACH
    // Time: O(m*n), Space: O(m*n)
    pair<int, string> longestCommonSubsequence_tabulation(string text1, string text2) {
        int m = text1.length(), n = text2.length();
        
        // DP table to store lengths
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        
        // Fill DP table
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                // If characters match
                if (text1[i-1] == text2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                }
                // If characters don't match
                else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        
        // Reconstruct the subsequence
        string subsequence;
        int i = m, j = n;
        while (i > 0 && j > 0) {
            // If characters match, add to subsequence
            if (text1[i-1] == text2[j-1]) {
                subsequence.push_back(text1[i-1]);
                i--; j--;
            }
            // Move in direction of larger value
            else if (dp[i-1][j] > dp[i][j-1]) {
                i--;
            }
            else {
                j--;
            }
        }
        
        // Reverse subsequence as we built it backwards
        reverse(subsequence.begin(), subsequence.end());
        
        // Return length and subsequence
        return {dp[m][n], subsequence};
    }
};

int main() {
    Solution sol;
    string text1 = "abcde";
    string text2 = "ace";
    
    // Recursive approach
    cout << "Recursive LCS Length: " 
         << sol.longestCommonSubsequence_recursive(text1, text2) << endl;
    
    // Memoization approach
    cout << "Memoization LCS Length: " 
         << sol.longestCommonSubsequence_memoization(text1, text2) << endl;
    
    // Tabulation approach with subsequence
    auto [length, subsequence] = sol.longestCommonSubsequence_tabulation(text1, text2);
    cout << "Tabulation LCS Length: " << length << endl;
    cout << "LCS Subsequence: " << subsequence << endl;
    
    return 0;
}