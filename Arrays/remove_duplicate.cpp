class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int uniqueIdx = 1; // track the unique index
        for (int i = 1; i < nums.size(); i++) {
             if (nums[i] != nums[i-1]) {
                nums[uniqueIdx++] = nums[i];
             }
        }
        return uniqueIdx;
    }
};
