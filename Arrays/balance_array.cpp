#include <string>

bool isBalanced(std::string num) {
    int evenSum = 0;
    int oddSum = 0;

    for (int i = 0; i < num.length(); ++i) {
        // Convert the character to a number
        int digit = num[i] - '0';

        if (i % 2 == 0) {
            // Even position
            evenSum += digit;
        } else {
            // Odd position
            oddSum += digit;
        }
    }

    return evenSum == oddSum;
}