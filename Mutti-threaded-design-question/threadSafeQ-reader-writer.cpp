#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <atomic>
#include <vector>
#include <shared_mutex> // For std::shared_mutex (C++17)

// Thread-safe queue implementation with minimal responsibilities
template <typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue;
    mutable std::mutex mutex;
    std::condition_variable cv;

public:
    // Push an item to the queue
    void push(const T& item) {
        {
            std::lock_guard<std::mutex> lock(mutex);
            queue.push(item);
        }
        // Notify one waiting thread that data is available
        cv.notify_one();
    }

    // Try to pop an item from the queue with timeout
    bool try_pop(T& item, const std::chrono::milliseconds& timeout) {
        std::unique_lock<std::mutex> lock(mutex);
        
        // Wait with timeout and predicate
        if (!cv.wait_for(lock, timeout, [this] { return !queue.empty(); })) {
            return false; // Timeout occurred and queue is still empty
        }
        
        item = queue.front();
        queue.pop();
        return true;
    }

    // Pop with blocking until item is available
    void pop(T& item) {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [this] { return !queue.empty(); });
        item = queue.front();
        queue.pop();
    }

    // Check if queue is empty
    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }

    // Get queue size
    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.size();
    }
};

// Global shared resources
ThreadSafeQueue<std::string> dataQueue;
std::atomic<bool> producerFinished{false};
std::shared_mutex rwMutex; // Reader-writer mutex for synchronizing console output

// Writer function
void writer(int numItems) {
    for (int i = 0; i < numItems; ++i) {
        std::string data = "String-" + std::to_string(i);
        
        // Push data to the queue
        dataQueue.push(data);
        
        // Use exclusive lock for writing to console
        {
            std::unique_lock<std::shared_mutex> writeLock(rwMutex);
            std::cout << "Writer produced: " << data << std::endl;
        }
        
        // Simulate some processing time
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    
    // Signal that production is complete
    producerFinished = true;
    std::cout << "Writer finished producing items." << std::endl;
}

// Reader function
void reader(int readerID) {
    std::string data;
    bool success = false;
    
    while (true) {
        // Try to get an item with timeout
        success = dataQueue.try_pop(data, std::chrono::milliseconds(100));
        
        if (success) {
            // Use shared lock for reading output
            std::shared_lock<std::shared_mutex> readLock(rwMutex);
            std::cout << "Reader " << readerID << " consumed: " << data << std::endl;
        }
        else if (producerFinished && dataQueue.empty()) {
            // Exit condition: producer is done and queue is empty
            std::cout << "Reader " << readerID << " exiting - no more data." << std::endl;
            break;
        }
        else {
            // If timeout occurred but there might be more data later, keep trying
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}

int main() {
    const int NUM_READERS = 5;
    const int NUM_ITEMS = 100;
    
    // Create writer thread
    std::thread writerThread(writer, NUM_ITEMS);
    
    // Create reader threads
    std::vector<std::thread> readerThreads;
    for (int i = 0; i < NUM_READERS; ++i) {
        readerThreads.emplace_back(reader, i);
    }
    
    // Join writer thread
    writerThread.join();
    
    // Join all reader threads
    for (auto& t : readerThreads) {
        t.join();
    }
    
    std::cout << "All threads finished." << std::endl;
    
    return 0;
}