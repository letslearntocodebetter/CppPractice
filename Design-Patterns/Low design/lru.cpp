#include <unordered_map>
#include <list>
#include <iostream>

class LRUCache {
private:
    int capacity;
    std::list<std::pair<int, int>> cacheList; // Doubly Linked List (stores key-value pairs)
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cacheMap; // Key -> Iterator

public:
    LRUCache(int cap) : capacity(cap) {}

    int get(int key) {
        if (cacheMap.find(key) == cacheMap.end()) return -1; // Key not found

        // Move accessed item to the front (most recently used)
        auto it = cacheMap[key];
        int value = it->second;
        cacheList.erase(it);
        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin();
        return value;
    }

    void put(int key, int value) {
        if (cacheMap.find(key) != cacheMap.end()) {
            // If key exists, remove it
            cacheList.erase(cacheMap[key]);
        } else if (cacheList.size() >= capacity) {
            // Evict least recently used (last element)
            auto lru = cacheList.back();
            cacheMap.erase(lru.first);
            cacheList.pop_back();
        }
        // Insert new element at the front
        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin();
    }

    void displayCache() {
        for (auto it : cacheList) {
            std::cout << "[" << it.first << ":" << it.second << "] ";
        }
        std::cout << "\n";
    }
}

class ThreadSafeLRUCache {
private:
    int capacity;
    std::list<std::pair<int, int>> cacheList; // Doubly Linked List
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cacheMap; // Key -> List Iterator
    std::mutex cacheMutex; // Mutex for thread safety

public:
    ThreadSafeLRUCache(int cap) : capacity(cap) {}

    int get(int key) {
        std::lock_guard<std::mutex> lock(cacheMutex); // Lock to ensure thread safety
        if (cacheMap.find(key) == cacheMap.end()) return -1; // Key not found

        // Move accessed item to the front (most recently used)
        auto it = cacheMap[key];
        int value = it->second;
        cacheList.erase(it);
        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin();
        return value;
    }

    void put(int key, int value) {
        std::lock_guard<std::mutex> lock(cacheMutex); // Lock to ensure thread safety

        if (cacheMap.find(key) != cacheMap.end()) {
            // If key exists, remove it
            cacheList.erase(cacheMap[key]);
        } else if (cacheList.size() >= capacity) {
            // Evict least recently used (last element)
            auto lru = cacheList.back();
            cacheMap.erase(lru.first);
            cacheList.pop_back();
        }

        // Insert new element at the front
        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin();
    }

    void displayCache() {
        std::lock_guard<std::mutex> lock(cacheMutex); // Lock for safe access
        for (auto it : cacheList) {
            std::cout << "[" << it.first << ":" << it.second << "] ";
        }
        std::cout << "\n";
    }
};

// ======== TESTING MULTITHREADING ========
#include <thread>

void threadTask(ThreadSafeLRUCache& cache, int id) {
    cache.put(id, id * 10);
    std::cout << "Thread " << id << " added: " << id << "\n";
    std::cout << "Thread " << id << " accessed: " << cache.get(id) << "\n";
}

// use readers write style locking

 std::unique_lock<std::shared_mutex> lock(mutex);
std::shared_lock<std::shared_mutex> lock(mutex);

int main() {
    ThreadSafeLRUCache lru(3);

    std::thread t1(threadTask, std::ref(lru), 1);
    std::thread t2(threadTask, std::ref(lru), 2);
    std::thread t3(threadTask, std::ref(lru), 3);
    std::thread t4(threadTask, std::ref(lru), 4); // Should evict LRU (1)

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    lru.displayCache(); // Should contain (4, 3, 2) since (1) is evicted
    return 0;
}
