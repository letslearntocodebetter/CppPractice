class Solution {
    public:
        string longestCommonPrefix(vector<string>& strs) {
            if (strs.size() == 0) return {};
    
            string prefix = strs.at(0);
            int commonLen = strs.at(0).size();
            
    
            for (int i=1; i < strs.size(); ++i) {
                // what is common in prefix and the string
                // that will become the next pefix
                int newLen = 0;
                // newLen is index, so if the match and come of the loop,
                // newLen will become size.
                while (newLen < commonLen && newLen < strs[i].size() 
                      && prefix[newLen] == strs[i][newLen]) {
                    newLen++;
                }
    
                if (newLen==0) return {};
                commonLen = newLen; 
            }
            return prefix.substr(0,commonLen); 
        }   
    };