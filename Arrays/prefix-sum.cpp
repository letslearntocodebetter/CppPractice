class NumArray {
    private:
        vector<int> prefix;
    public:
        NumArray(vector<int>& nums) {
            int n = nums.size();
            prefix.resize(n + 1, 0);
            for (int i = 0; i < n; i++) {
                prefix[i + 1] = prefix[i] + nums[i];
            }
        }
        
        int sumRange(int left, int right) {
            return prefix[right + 1] - prefix[left];
        }
    };
   
//     This is because prefix[i] always represents the sum up to but not including index i in nums.
//     voids Extra Conditions for Left Bound (left = 0)
// If we used size n, handling sumRange(0, j) would be tricky because we'd need a special case to return prefix[j] directly.