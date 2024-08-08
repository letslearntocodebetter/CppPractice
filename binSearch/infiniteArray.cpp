// just double the search index values

class Solution {
public:
    int findPosition(const vector<int>& arr, int target) {
        // First, find a range where the target might exist
        int start = 0;
        int end = 1;
        
        // Exponentially increase the range until we find a range that might contain the target
        while (target >= arr[end]) {
            start = end;
            end = std::min(array.size() - 1, end * 2);
        }
        // Perform binary search in the found range
        return binarySearch(arr, target, start, end);
    }

private:
    int binarySearch(const vector<int>& arr, int target, int start, int end) {
        while (start <= end) {
            int mid = start + (end - start) / 2;
            
            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }
        
        return -1; // Target not found
    }
};