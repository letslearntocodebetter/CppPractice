int findMaxInBitonicArray(const std::vector<int>& nums) {
    int left = 0, right = nums.size() - 1;

    // Handle boundary conditions
    if (nums.size() == 1 || nums[0] > nums[1]) {
        return nums[0];
    }
    
    if (nums[right] > nums[right - 1]) {
        return nums[right];
    }

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Simplified check for the maximum element
        if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]) {
            return nums[mid];
        }
        // If mid is part of the increasing sequence, move to the right
        else if (nums[mid] < nums[mid + 1]) {
            left = mid + 1;
        }
        // If mid is part of the decreasing sequence, move to the left
        else {
            right = mid - 1;
        }
    }

    // Should never reach here if the input is a valid bitonic array
    return -1;
}

#include <iostream>
#include <vector>

// Function to find the maximum element in a bionic array
// Using simplified comparison logic
int findMaxInBionicArray(const std::vector<int>& arr) {
    int n = arr.size();
    
    // Handle edge cases
    if (n == 0) return -1; // Empty array
    if (n == 1) return arr[0]; // Single element
    
    int left = 0;
    int right = n - 1;
    
    // Binary search to find the peak element
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int prev = (mid - 1 + n) % n; // Handle wrap-around for first element
        int next = (mid + 1) % n;     // Handle wrap-around for last element
        
        // Check if mid is the peak
        if (arr[mid] >= arr[prev] && arr[mid] >= arr[next]) {
            return arr[mid];
        }
        
        // If next element is greater, move right (we're on increasing side)
        else if (arr[mid] < arr[next]) {
            left = mid + 1;
        }
        // If next element is smaller, move left (we're on decreasing side)
        else {
            right = mid - 1;
        }
    }
    
    // This should not be reached for a valid bionic array
    return arr[0];
}
