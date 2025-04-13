#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

class RodCutting {
public:
    /**
     * Top-down recursive approach for Rod Cutting problem
     * 
     * price[i] is the price of a rod of length i+1
     * n is the length of the rod to be cut
     * 
     * Time Complexity: O(n^2) - we have n possible lengths, and for each length,
     *                           we try up to n different cuts
     * Space Complexity: O(n) for the recursion call stack
     */
    int cutRod_recursive(vector<int>& price, int n) {
        // Base case: if length is 0, no profit can be made
        if (n <= 0) return 0;
        
        // Initialize result as minimum possible value
        int maxVal = INT_MIN;
        
        // Consider all possible cuts and take the maximum
        for (int i = 0; i < n; i++) {
            // price[i] is price for length (i+1)
            // We're cutting a piece of length (i+1) and recursively 
            // solving for the remaining length (n-(i+1))
            maxVal = max(maxVal, price[i] + cutRod_recursive(price, n - (i + 1)));
        }
        
        return maxVal;
    }
    
    /**
     * Bottom-up tabulation approach for Rod Cutting problem
     * 
     * Time Complexity: O(n^2)
     * Space Complexity: O(n) for the dp array
     */
    int cutRod_tabulation(vector<int>& price, int n) {
        // dp[i] stores the maximum value obtainable for a rod of length i
        vector<int> dp(n + 1, 0);
        
        // Build the table in bottom-up manner
        for (int i = 1; i <= n; i++) {
            int maxVal = INT_MIN;
            
            // Consider all possible ways to cut a rod of length i
            for (int j = 0; j < i; j++) {
                // Cut a piece of length (j+1) and use optimal solution for remaining length
                maxVal = max(maxVal, price[j] + dp[i - (j + 1)]);
            }
            
            dp[i] = maxVal;
        }
        
        return dp[n];
    }
    
    /**
     * Alternative tabulation approach using 2D array
     * This approach explicitly shows the unbounded knapsack structure
     * 
     * Time Complexity: O(n^2)
     * Space Complexity: O(n^2) for the 2D dp array
     */
    int cutRod_tabulation_2D(vector<int>& price, int n) {
        // Create lengths array: lengths[i] is the length of the piece (i+1)
        vector<int> lengths(n);
        for (int i = 0; i < n; i++) {
            lengths[i] = i + 1;
        }
        
        // dp[i][j] represents the maximum value obtainable from a rod of length j
        // using the first i types of pieces
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        
        // Fill the dp table
        for (int i = 1; i <= n; i++) {  // For each length option
            for (int j = 1; j <= n; j++) {  // For each rod length
                // Current piece length
                int currentLength = lengths[i-1];
                
                // Current piece price
                int currentPrice = price[i-1];
                
                if (currentLength <= j) {
                    // Two options:
                    // 1. Include this piece (can use same piece again since it's unbounded)
                    // 2. Exclude this piece
                    dp[i][j] = max(currentPrice + dp[i][j - currentLength], dp[i-1][j]);
                } else {
                    // Cannot use this piece because it's too long
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        
        return dp[n][n];
    }
};

int main() {
    RodCutting solver;
    
    // Example 1: Price array for lengths 1, 2, 3, ..., n
    vector<int> price1 = {1, 5, 8, 9, 10, 17, 17, 20};
    int n1 = price1.size();
    
    cout << "Rod length: " << n1 << endl;
    cout << "Price array: [";
    for (int i = 0; i < price1.size(); i++) {
        cout << price1[i];
        if (i < price1.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    cout << "Maximum obtainable value (Recursive): " 
         << solver.cutRod_recursive(price1, n1) << endl;
    cout << "Maximum obtainable value (Tabulation): " 
         << solver.cutRod_tabulation(price1, n1) << endl;
    cout << "Maximum obtainable value (2D Tabulation): " 
         << solver.cutRod_tabulation_2D(price1, n1) << endl;
    
    // Example 2: Another price array
    vector<int> price2 = {3, 5, 8, 9, 10, 17, 17, 20};
    int n2 = price2.size();
    
    cout << "\nRod length: " << n2 << endl;
    cout << "Price array: [";
    for (int i = 0; i < price2.size(); i++) {
        cout << price2[i];
        if (i < price2.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    cout << "Maximum obtainable value (Recursive): " 
         << solver.cutRod_recursive(price2, n2) << endl;
    cout << "Maximum obtainable value (Tabulation): " 
         << solver.cutRod_tabulation(price2, n2) << endl;
    cout << "Maximum obtainable value (2D Tabulation): " 
         << solver.cutRod_tabulation_2D(price2, n2) << endl;
    
    return 0;
}