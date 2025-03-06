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

int main() {
    std::vector<int> bitonicArray = {1, 3, 8, 12, 4, 2};
    int maxElement = findMaxInBitonicArray(bitonicArray);
    std::cout << "The maximum element in the bitonic array is: " << maxElement << std::endl;
    return 0;
}
