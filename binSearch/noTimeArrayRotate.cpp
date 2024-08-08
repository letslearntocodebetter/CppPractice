#include <vector>

class RotationCounter {
public:
    int countRotations(const std::vector<int>& arr) {
        int left = 0;
        int right = arr.size() - 1;

        // If the array is not rotated at all
        if (arr[left] <= arr[right]) return 0;

        while (left <= right) {
            // If there are only two elements left
            if (right == left + 1) {
                return (arr[right] < arr[left]) ? right : left;
            }

            int mid = left + (right - left) / 2;


            if (a[mid]  < a[mid -1] && a[mid] > a[mid+1]) return mid;

            // if (arr[mid] < arr[mid - 1]) {
            //     return mid;
            // }

            // Check which half to search in
            if (arr[mid] > arr[right]) {
                // Minimum is in the right half
                left = mid + 1;
            } else {
                // Minimum is in the left half
                right = mid - 1;
            }
        }

        return 0;  // This line should never be reached for a valid input
    }
};