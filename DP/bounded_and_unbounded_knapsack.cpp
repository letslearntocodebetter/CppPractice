Comparing Different Knapsack Problem Variants
1. 0/1 Knapsack (Bounded Knapsack)

Constraint: Each item can be used at most once
State Transition: dp[i][w] = max(dp[i-1][w], dp[i-1][w-weight[i-1]] + value[i-1])
Examples:

Traditional knapsack problem
Subset sum
Equal sum partition



2. Unbounded Knapsack

Constraint: Each item can be used any number of times
State Transition: dp[i][w] = max(dp[i-1][w], dp[i][w-weight[i-1]] + value[i-1])

Note the difference in the second term: dp[i][w-weight[i]] instead of dp[i-1][w-weight[i]]


Examples:

Coin Change
Rod Cutting
Ribbon Cutting
Maximum Product Cutting


