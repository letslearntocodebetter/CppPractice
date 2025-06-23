
int findMaxInBitonicArray(const std::vector<int>& nums) {
    int n = nums.size();
    
    // Handle boundary conditions
    if (n == 1) return nums[0];
    if (nums[0] > nums[1]) return nums[0];
    if (nums[n-1] > nums[n-2]) return nums[n-1];
    
    int left = 1, right = n - 2;  // We already checked indices 0 and n-1
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Check if mid is the peak
        if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]) {
            return nums[mid];
        }
        // If mid is part of the increasing sequence
        else if (nums[mid] < nums[mid + 1]) {
            left = mid + 1;
        }
        // If mid is part of the decreasing sequence
        else {
            right = mid - 1;
        }
    }
    
    // Should never reach here if the input is a valid bitonic array
    return -1;
}
            right = mid - 1;
        }
    }
    
    // This should not be reached for a valid bionic array
    return arr[0];
}
