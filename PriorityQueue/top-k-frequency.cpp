#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue> // Priority queue for min-heap

// That's a very sharp question! It's great that you're thinking about why we chose a min-heap instead of a max-heap. It might seem like a max-heap would be more straightforward, right?

// Here's why we use a min-heap:

// The Goal: Top "K" Elements

// Our goal isn't to find all the most frequent elements. We only want the top "K" most frequent ones.
// This means we don't need to keep track of every element's frequency. We only need to keep track of the top "K" frequencies we've seen so far.
// Why a Min-Heap Works Best

// Keeping Track of the "Bottom" of the Top "K":

// A min-heap lets us easily find the smallest frequency among the top "K" elements we've seen.
// Think of it like a "cut-off" point. If a new element's frequency is greater than the smallest frequency in our min-heap, it means it's worthy of being in the top "K."
// Efficient Replacement:

// When we find a new element with a frequency greater than the smallest frequency in our min-heap, we can quickly replace the smallest frequency with the new one.
// The min-heap helps us do this efficiently.
// Avoiding Unnecessary Storage:

// If we used a max-heap, we'd have to keep track of all the frequencies we've seen, even the ones that are very small.
// The min-heap lets us focus only on the frequencies that matter: the top "K."
// Imagine a Race

// Imagine a race where only the top "K" runners get a medal.
// A min-heap is like a way to keep track of the slowest runner who's currently in the medal positions.
// If a new runner is faster than that slowest medal-holder, they get to take their place.


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
