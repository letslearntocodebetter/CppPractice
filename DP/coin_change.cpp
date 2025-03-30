#include <iostream>
#include <vector>
#include <climits> // For INT_MAX

int coinChange2D(std::vector<int>& coins, int amount) {
    int numCoins = coins.size();
    std::vector<std::vector<int>> dp(numCoins + 1, std::vector<int>(amount + 1, INT_MAX));

    // Base case: 0 amount needs 0 coins
    for (int i = 0; i <= numCoins; ++i) {
        dp[i][0] = 0;
    }

    for (int i = 1; i <= numCoins; ++i) {
        for (int j = 1; j <= amount; ++j) {
            if (coins[i - 1] <= j) {
                // We can either not use the current coin, or use it
                if(dp[i][j - coins[i-1]] != INT_MAX){
                    dp[i][j] = std::min(dp[i - 1][j], dp[i][j - coins[i - 1]] + 1);
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            } else {
                // Current coin is too large, we can't use it
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return (dp[numCoins][amount] == INT_MAX) ? -1 : dp[numCoins][amount];
}

int main() {
    std::vector<int> coins = {1, 2, 5};
    int amount = 11;

    int result = coinChange2D(coins, amount);

    std::cout << "Minimum coins needed: " << result << std::endl;

    return 0;
}