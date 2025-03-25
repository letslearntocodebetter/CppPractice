#include <iostream>
#include <vector>
#include <limits>

int maxProfit(const std::vector<int>& prices) {
    if (prices.empty()) return 0; // Edge case: No prices

    int buyprice = price[0]; / INT_MAX;
    int maxProfit = 0;
    // keep tarck of min seen so far
    // and keep track of max so far

    for (int i = 1; i < prices.size(); ++if)
    {
        buyPrice = std::min(buyPrice, price[i]);
        int currentProfit = price[i] - buyPrice;
        maxProfit = std::max(currentProfit, maxProfit)
    }
    
    return maxProfit;
}

// Example Usage
int main() {
    std::vector<int> prices = {7, 1, 5, 3, 6, 4};
    std::cout << "Max Profit: " << maxProfit(prices) << std::endl;
    return 0;
}
