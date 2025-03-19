#include <stack>
#include <unordered_map>

// If you're using C++17 or earlier, replace .contains(c) with matching.count(c) > 0.
class Solution {
public:
    bool isSymbol(char c) {
        return c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']';
    }

    bool isValid(std::string s) {
        std::stack<char> symbols;
        std::unordered_map<char, char> matching = {{')', '('}, {'}', '{'}, {']', '['}};
        
        for (char c : s) {
            if (!isSymbol(c)) continue;  // Skip non-symbol characters
            
            if (matching.contains(c)) {  // If it's a closing bracket
                if (symbols.empty() || symbols.top() != matching[c]) {
                    return false;
                }
                symbols.pop();
            } else {  // If it's an opening bracket
                symbols.push(c);
            }
        }
        
        return symbols.empty();
    }
};
