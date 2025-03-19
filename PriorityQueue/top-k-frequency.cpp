#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue> // Priority queue for min-heap

std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
    // 1. Count frequency of each number
    std::unordered_map<int, int> counts;
    for (int num : nums) {
        counts[num]++;
    }

    // 2. Min-heap to store the top k elements (min frequency at the top)
    using Pair = std::pair<int, int>; // (frequency, number)
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> minHeap;

    for (const auto& [num, count] : counts) {
        if (minHeap.size() < k) {
            minHeap.push({count, num});  // Directly insert if heap size < k
        } 
        else if (count > minHeap.top().first) {  
            minHeap.pop();   // Remove smallest frequency
            minHeap.push({count, num});  // Insert the new element
        }
    }

    // 2. Alternate approach

for (const auto& [num, count] : counts) { 
    minHeap.emplace(count, num);  // Use emplace() instead of push()
    if (minHeap.size() > k) {  
        minHeap.pop();  // Always remove the smallest element if heap exceeds k
    }
}



    // 3. Extract the top k elements
    std::vector<int> result;
    result.reserve(k); // Reserve space to avoid reallocations

    while (!minHeap.empty()) {
        result.push_back(minHeap.top().second);
        minHeap.pop();
    }

    return result;
}

int main() {
    std::vector<int> nums = {1, 1, 1, 2, 2, 3};
    int k = 2;
    std::vector<int> top = topKFrequent(nums, k);

    std::cout << "Top " << k << " frequent elements: ";
    for (int num : top) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
