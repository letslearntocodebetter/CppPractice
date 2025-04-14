/**
Algorithm
Sort the input array.
1. Iterate through the array with index i.
2. For each i, set two pointers: left = i+1 and right = array.size()-1.
2. Find pairs where nums[left] + nums[right] = -nums[i].
3. Skip duplicate values to avoid duplicate triplets.
*/

#include <vector>
#include <algorithm> // For sort function

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        
        // Edge case: if array has less than 3 elements, return empty result
        if (nums.size() < 3) {
            return result;
        }
        
        // Step 1: Sort the array
        std::sort(nums.begin(), nums.end());
        
        // Step 2: Iterate through the array
        for (int i = 0; i < nums.size() - 2; i++) {
            // Skip duplicate values for i
            if (i > 0 && nums[i] == nums[i-1]) {
                continue;
            }
            
            // Set two pointers
            int left = i + 1;
            int right = nums.size() - 1;
            
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                
                if (sum < 0) {
                    // If sum is too small, move left pointer to increase sum
                    left++;
                } else if (sum > 0) {
                    // If sum is too large, move right pointer to decrease sum
                    right--;
                } else {
                    // Found a triplet with sum = 0
                    result.push_back({nums[i], nums[left], nums[right]});
                    
                    // Skip duplicates for left pointer
                    while (left < right && nums[left] == nums[left + 1]) {
                        left++;
                    }
                    
                    // Skip duplicates for right pointer
                    while (left < right && nums[right] == nums[right - 1]) {
                        right--;
                    }
                    
                    // Move both pointers inward
                    left++;
                    right--;
                }
            }
        }
        
        return result;
    }
};
