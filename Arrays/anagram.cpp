// Approach 1: Sorting
bool isAnagramSort(string s, string t) {
    if (s.length() != t.length()) return false;
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    return s == t;
}

// Approach 2: Frequency Count (Hash Table)
bool isAnagramCount(string s, string t) {
    if (s.length() != t.length()) return false;
    
    unordered_map<char, int> count;
    for (char c : s) count[c]++;
    for (char c : t) {
        if (--count[c] < 0) return false;
    }
    
    return true;
}