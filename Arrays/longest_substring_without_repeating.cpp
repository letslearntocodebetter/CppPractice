using namespace std;
#include <iostream>
#include <unordered_map>
#include <string>

int longestSubSequence(const std::string &s) {
    std::unordered_map<char, int> lastIndex;
    int maxSize = 0;
    int start = 0;

    for (int i = 0; i < s.length(); ++i) {
        char ch = s[i];
        if (lastIndex.contains(ch) && lastIndex[ch] >= start) {
            start = lastIndex[ch] + 1;  // move start to one past the last occurrence
        }
        lastIndex[ch] = i;
        maxSize = std::max(maxSize, i - start + 1);
    }

    return maxSize;
}

int main() {
    std::string input;
    std::cout << "Enter a string: ";
    std::cin >> input;

    int result = lengthOfLongestSubstring(input);
    std::cout << "Length of longest substring without repeating characters: " << result << std::endl;

    return 0;
}
