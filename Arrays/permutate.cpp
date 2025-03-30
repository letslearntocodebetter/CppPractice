#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Function to generate permutations and store them in a vector
void permute(string str, int l, int r, vector<string>& result) {
    if (l == r) {
        result.push_back(str); // Store the permutation in the vector
    } else {
        for (int i = l; i <= r; i++) {
            swap(str[l], str[i]); // Swap characters to fix one character at position l
            permute(str, l + 1, r, result); // Recur for the remaining substring
            swap(str[l], str[i]); // Backtrack to restore the original string before the next iteration
            // Backtracking ensures that we revert to the original configuration before making the next swap,
            // allowing us to explore all possible permutations without permanent modifications.
        }
    }
}

int main() {
    string s;
    cout << "Enter a string: ";
    cin >> s;
    vector<string> permutations;
    permute(s, 0, s.length() - 1, permutations);
    
    cout << "Permutations of " << s << ":" << endl;
    for (const string& perm : permutations) {
        cout << perm << endl;
    }
    return 0;
}
