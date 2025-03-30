#include <vector>
#include <iostream>
using namespace std;

void merge(vector<int> &arr, int left, int mid, int right) {
    // Size of left and right subarrays
    int sizeLeft = mid - left + 1;  // Includes mid
    int sizeRight = right - mid;    // Excludes mid

    // Create two subarrays using vector constructor
    vector<int> leftArr(arr.cbegin() + left, arr.begin() + mid + 1);
    vector<int> rightArr(arr.cbegin() + mid + 1, arr.begin() + right + 1);

    // alternative
 // for (i = 0 ; i < leftsize; i++)
 //   leftArr[i] = arr[left + i]
    // for ( j =0; j < rifghtSize; j++)
 //   rightArr[j] = arr[mid + 1 + j]


    // Indices for left and right subarrays
    size_t i = 0, j = 0;
    int k = left;  // Start index for merging back into original array

    // Merge step: Compare elements from both subarrays and place the smallest in arr[]
    while (i < sizeLeft && j < sizeRight) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    // Copy remaining elements from leftArr (if any)
    while (i < sizeLeft) {
        arr[k++] = leftArr[i++];
    }

    // Copy remaining elements from rightArr (if any)
    while (j < sizeRight) {
        arr[k++] = rightArr[j++];
    }
}

void mergeSort(std::vector<int>& arr, size_t left, size_t right) 
{
    if (left < right) {
        // divide the arr
        mid = left + (right - left) /2;

        mergeSort(arr, left, mid);
        mergSort(arr, mid + 1, right);
        merge(arr, left, mid, right);

    }
}

int hoarePartition(std::vector<int>& arr, size_t left, size_t right) {
    int pivot = arr[left];  // Choose pivot as the first element
    int i = left;           // Start i at left
    int j = right;          // Start j at right

    while (true) {
        // Move i right until we find an element >= pivot
        while (arr[i] < pivot) {
            i++;  // Increment i to find an element >= pivot
        }

        // Move j left until we find an element <= pivot
        while (arr[j] > pivot) {
            j--;  // Decrement j to find an element <= pivot
        }

        // If indices cross, partitioning is done
        if (i >= j) {
            return j; // Return partition index
        }

        // Swap elements to partition the array
        std::swap(arr[i], arr[j]);
    }
    std::swap(arr[left], arr[j]); 
    return j;
}
