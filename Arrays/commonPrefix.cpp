class Solution {
    public:
        string longestCommonPrefix(vector<string>& strs) {
            if (strs.size() == 0) return {};
    
            string prefix = strs.at(0);
            int commonLen = strs.at(0).size(); // this is index +1
            
    
            // iterator to the string

            for (int i = 1; i < strs.size(); ++i) {
                 auto currStr = strs[i];
                // what is common in prefix and the string
                // that will become the next pefix
                int newLen = 0;
                // newLen is index, so if the match and come of the loop,
                // newLen will become size.
                while (newLen < commonLen && newLen < currStr.size() 
                      && prefix[newLen] == currStr[newLen]) {
                    newLen++; // index, and now exceeds from 
                }
    
                if (newLen==0) return {};
                // update the commonLength for next iteration
                commonLen = newLen; 
            }
            return prefix.substr(0,commonLen); 
        }   
    };