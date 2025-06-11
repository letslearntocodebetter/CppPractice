#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <chrono>
#include <algorithm>

const int ARRAY_SIZE = 1000;

// Generate test data
std::vector<int> generateArray() {
    std::vector<int> arr(ARRAY_SIZE);
    std::iota(arr.begin(), arr.end(), 1); // Fill with 1, 2, 3, ..., 1000
    return arr;
}

// IMPLEMENTATION 1: Using std::thread
// Pros: Direct control over threads, explicit synchronization
// Cons: Manual thread management, need to handle join operations
long long sumWithThreads(const std::vector<int>& arr) {
    const int numThreads = std::thread::hardware_concurrency();
    const int chunkSize = ARRAY_SIZE / numThreads;
    
    std::vector<std::thread> threads;
    std::vector<long long> partialSums(numThreads, 0);
    
    // Create threads to process chunks of the array
    for (int i = 0; i < numThreads; ++i) {
        int start = i * chunkSize;
        int end = (i == numThreads - 1) ? ARRAY_SIZE : (i + 1) * chunkSize;
        
        threads.emplace_back([&arr, &partialSums, i, start, end]() {
            for (int j = start; j < end; ++j) {
                partialSums[i] += arr[j];
            }
        });
    }
    
    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }
    
    // Sum up all partial results
    return std::accumulate(partialSums.begin(), partialSums.end(), 0LL);
}

// IMPLEMENTATION 2: Using std::future and std::promise
// Pros: Clean separation of result retrieval, good for complex computations
// Cons: More complex setup, overkill for simple operations
long long sumWithPromise(const std::vector<int>& arr) {
    const int numThreads = std::thread::hardware_concurrency();
    const int chunkSize = ARRAY_SIZE / numThreads;
    
    std::vector<std::future<long long>> futures;
    std::vector<std::promise<long long>> promises(numThreads);
    
    // Create futures from promises
    for (int i = 0; i < numThreads; ++i) {
        futures.push_back(promises[i].get_future());
    }
    
    std::vector<std::thread> threads;
    
    // Create threads that will set promise values
    for (int i = 0; i < numThreads; ++i) {
        int start = i * chunkSize;
        int end = (i == numThreads - 1) ? ARRAY_SIZE : (i + 1) * chunkSize;
        
        threads.emplace_back([&arr, &promises, i, start, end]() {
            long long sum = 0;
            for (int j = start; j < end; ++j) {
                sum += arr[j];
            }
            promises[i].set_value(sum); // Set the promise value
        });
    }
    
    // Collect results from futures
    long long totalSum = 0;
    for (auto& future : futures) {
        totalSum += future.get(); // This blocks until the result is available
    }
    
    // Clean up threads
    for (auto& t : threads) {
        t.join();
    }
    
    return totalSum;
}

// IMPLEMENTATION 3: Using std::async
// Pros: Simplest code, automatic thread management, clean and readable
// Cons: Less control over thread creation, may use thread pool
long long sumWithAsync(const std::vector<int>& arr) {
    const int numThreads = std::thread::hardware_concurrency();
    const int chunkSize = ARRAY_SIZE / numThreads;
    
    std::vector<std::future<long long>> futures;
    
    // Launch async tasks
    for (int i = 0; i < numThreads; ++i) {
        int start = i * chunkSize;
        int end = (i == numThreads - 1) ? ARRAY_SIZE : (i + 1) * chunkSize;
        
        // std::launch::async ensures the task runs asynchronously
        futures.push_back(std::async(std::launch::async, [&arr, start, end]() {
            long long sum = 0;
            for (int j = start; j < end; ++j) {
                sum += arr[j];
            }
            return sum;
        }));
    }
    
    // Collect results - futures automatically handle synchronization
    long long totalSum = 0;
    for (auto& future : futures) {
        totalSum += future.get();
    }
    
    return totalSum;
}


/**
std::async(launch_policy, function, arguments...)
Launch Policies:

std::launch::async

Forces asynchronous execution
Always creates new thread(s)
Guarantees parallel execution
Does NOT typically use thread pool


std::launch::deferred

Lazy evaluation - runs when .get() is called
Executes on the calling thread
No parallelism - essentially synchronous
Useful for conditional execution


std::launch::async | std::launch::deferred (Default)

Implementation chooses the strategy
MAY use thread pool (implementation-dependent)
MAY create new threads or defer execution
Most flexible but least predictable



Thread Pool Behavior:
Key Points:
*/
// Benchmark function

template<typename Func>
void benchmark(const std::string& name, Func func, const std::vector<int>& arr) {
    auto start = std::chrono::high_resolution_clock::now();
    long long result = func(arr);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << name << ": " << result << " (Time: " << duration.count() << " μs)\n";
}

int main() {
    std::cout << "Available CPU cores: " << std::thread::hardware_concurrency() << "\n\n";
    
    auto arr = generateArray();
    
    // Sequential sum for comparison
    auto start = std::chrono::high_resolution_clock::now();
    long long sequentialSum = std::accumulate(arr.begin(), arr.end(), 0LL);
    auto end = std::chrono::high_resolution_clock::now();
    auto seqDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Sequential sum: " << sequentialSum << " (Time: " << seqDuration.count() << " μs)\n\n";
    
    // Test all three parallel implementations
    benchmark("std::thread", sumWithThreads, arr);
    benchmark("std::promise/future", sumWithPromise, arr);
    benchmark("std::async", sumWithAsync, arr);
    
    return 0;
}

/*
COMPARISON AND ANALYSIS:

1. std::thread Implementation:
   - COMPLEXITY: Medium
   - PROS: Direct control, explicit thread management, predictable behavior
   - CONS: Manual synchronization, more boilerplate code, need to handle joins
   - BEST FOR: When you need fine control over thread behavior

2. std::promise/future Implementation:
   - COMPLEXITY: High
   - PROS: Clean separation of computation and result retrieval, good for complex async patterns
   - CONS: Most verbose, overkill for simple operations, harder to understand
   - BEST FOR: Complex async operations where you need to pass results between threads

3. std::async Implementation:
   - COMPLEXITY: Low
   - PROS: Simplest and cleanest code, automatic thread management, most readable
   - CONS: Less control over thread creation, implementation-dependent behavior
   - BEST FOR: Simple parallel computations, prototyping, general use

WINNER: std::async
- Simplest to write and understand
- Least error-prone
- Automatic resource management
- Clean, readable code
- Perfect for this type of parallel computation

For most use cases involving parallel computation of independent tasks,
std::async is the recommended approach due to its simplicity and safety.
*/