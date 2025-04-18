#include <iostream>
#include <vector>

int findSingleElement(const std::vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;
    
    // Handle edge cases
    if (right == 0) return nums[0];
    if (nums[0] != nums[1]) return nums[0];
    if (nums[right] != nums[right - 1]) return nums[right];
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Check if mid is the single element
        if (nums[mid] != nums[mid - 1] && nums[mid] != nums[mid + 1]) {
            return nums[mid];
        }
        
        // Check if mid is even or odd
        bool isEven = (mid % 2 == 0);
        
        if ((isEven && nums[mid] == nums[mid + 1]) || 
            (!isEven && nums[mid] == nums[mid - 1])) {
            // We are on the left side of the single element
            left = mid + 1;
        } else {
            // We are on the right side of the single element
            right = mid - 1;
        }
    }
    
    // Should not reach here if input is valid
    return -1;
}
