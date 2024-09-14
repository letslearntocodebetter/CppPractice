// the idea is to find the part which is sorted,
// the other part will not be sorted
// search in the sorted part



class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (target == nums[mid]) {
                return mid;
            }
            
            // left is sorted
            if (nums[left] >= nums[mid]) {
                if (target >= nums[left] && target < nums[mid]) {
                    right = mid -1;
                } else {
                    left = mid + 1;
                }
            } else {
                if (target > nums[mid] && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid -1;
                }
            }
        }
        return -1; // Element not found
    }
};