// totated element will be smaller than both of its neighbors.
// the min point will aloways fall on the unsorted part of the array.

int findRotationCount(const std::vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    int n = arr.size();
   
   // check the boundry conditions first
    if (arr[left] <= arr[right]) {
        return 0;
    }
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        int prev = (mid - 1 + n) % n;
        int next = (mid + 1) % n;

        // this is the peak the smallest elment from both the neightbous

        if (arr[mid] <= arr[prev] && arr[mid] <= arr[next]) {
            return mid;
        }
       // Only compare the RIGHT INDEX there is no need to cosider left one

       
       // the rotated array will always be lying on the non sorted side.
        // 1. if left > mid 
        // meaning it is sorted arry and then we must find on the other side
        // 2. if left > 

        if (a[mid] >= a[right]) {
            left = mid + 1;
        } else if ( a[mid] < = a[right]) {
            right = mid -1
        }
    return 0;

}