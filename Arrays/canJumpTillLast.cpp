class Solution {
    public:
        bool canJump(vector<int>& nums) {
           // go from the back direction and see if we can reach to the index
           int currentGoal = nums.size() - 1;
    
           for (int i = nums.size() - 2; i >=0 ; --i) {
               if (i + nums[i] >= currentGoal) {
                currentGoal = i;
               }
           }
           return currentGoal == 0;
        }
    };