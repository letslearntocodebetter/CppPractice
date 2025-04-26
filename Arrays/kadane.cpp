// We’ll keep three more variables:
// start: temporary start of the current subarray.
// begin: actual start of the max subarray.
// end: actual end of the max subarray.

// Each time currentSum is reset to the current element, update start to that index.
// If currentSum becomes the new maxSum, update begin and end.



int kadaneWithIndices(const vector<int>& nums, int& begin, int& end) {
    int currentSum = nums[0];
    int maxSum = nums[0];
    
    begin = 0;
    end = 0;
    int start = 0;  // Temporary start index

    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] > currentSum + nums[i]) { // the sum is negetive so far so drop it;
            currentSum = nums[i];
            start = i; // Start new subarray
        } else {
            currentSum += nums[i]; // else dont do anything
        }

        if (currentSum > maxSum) { // record when indcies
            maxSum = currentSum;
            begin = start;
            end = i;
        }
    }

    return maxSum;
}
int main() {
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    int startIndex = 0, endIndex = 0;
    int maxSubarraySum = kadaneWithIndices(arr, startIndex, endIndex);

    cout << "Maximum Subarray Sum is: " << maxSubarraySum << endl;
    cout << "Subarray starts at index " << startIndex 
         << " and ends at index " << endIndex << endl;

    cout << "Subarray: ";
    for (int i = startIndex; i <= endIndex; ++i)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
