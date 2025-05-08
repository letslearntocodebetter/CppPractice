//prefix[i] = sum of nums[0..i]
//You are at index j, and prefix sum is S = prefix[j]

//If you saw a previous sum = S - k at index i,
//then nums[i+1 to j] must sum to k
Because:
//prefix[j] - prefix[i] = k
=> sum of subarray (i+1 to j) = k
// 

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        // Hash map to store the number of times a particular prefix sum has occurred.
        unordered_map<int, int> prefix;

        // Initialize with prefix sum 0 occurring once.
        // This handles cases where the subarray itself starts from index 0.
        prefix[0] = 1;

        int count = 0;  // To store the total number of subarrays that sum to k
        int sum = 0;    // Running prefix sum

        // Iterate through the array
        for (int num : nums) {
            sum += num;  // Update the running prefix sum

            // Check if there is a prefix sum that if removed from current sum gives k
            // i.e., check if (sum - k) exists in the map
            if (prefix.contains(sum - k)) {
                count += prefix[sum - k];  // Add the number of such prefix sums to the count
            }

            // Store the current prefix sum in the map
            // This will be used for future elements
            prefix[sum]++;
        }

        // Return the total count of subarrays that sum to k
        return count;
    }
};
