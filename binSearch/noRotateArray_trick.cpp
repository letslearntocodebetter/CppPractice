int findRotationCount(const std::vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    int n = arr.size();
    if (arr[left] <= arr[right]) {
        return 0;
    }
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int prev = (mid - 1 + n) % n;
        int next = (mid + 1) % n;
        if (arr[mid] <= arr[prev] && arr[mid] <= arr[next]) {
            return mid;
        }
        if (arr[mid] <= arr[right]) {
            right = mid - 1;
        } else if (arr[mid] >= arr[left]) {
            left = mid + 1;
        }
    }
    return 0;
}