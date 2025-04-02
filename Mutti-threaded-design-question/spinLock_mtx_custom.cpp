#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

// Spinlock class
class Spinlock {
private:
    std::atomic<bool> flag;

public:
    Spinlock() : flag(false) {}

    // Acquire lock using a busy-wait loop (spinlock)
    void lock() {
        while (flag.exchange(true, std::memory_order_acquire)) {
            // Spin (busy-wait) until the lock becomes available
            std::this_thread::yield(); // Yield to other threads to prevent excessive CPU usage
        }
    }

    // Release the lock
    void unlock() {
        flag.store(false, std::memory_order_release);
    }
};

// Function to demonstrate spinlock usage
void critical_section(int id, Spinlock& lock) {
    lock.lock();
    std::cout << "Thread " << id << " is in the critical section.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
    std::cout << "Thread " << id << " is leaving the critical section.\n";
    lock.unlock();
}

int main() {
    Spinlock spinlock;
    const int num_threads = 5;
    std::vector<std::thread> threads;

    // Launch multiple threads
    for (int i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread(critical_section, i, std::ref(spinlock)));
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}


