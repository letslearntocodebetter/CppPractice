#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <atomic>
#include <type_traits>

class ThreadPool {
private:
    // Worker threads
    std::vector<std::thread> workers;
    
    // Task queue
    std::queue<std::function<void()>> tasks;
    
    // Synchronization primitives
    mutable std::mutex queue_mutex;
    std::condition_variable condition;
    
    // Shutdown flag
    std::atomic<bool> stop{false};

    // Worker thread function - extracted from constructor
    void worker_thread() {
        // Worker thread main loop
        while (true) {
            std::function<void()> task;
            
            // Critical section: get task from queue
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                
                // Wait for task or shutdown signal
                condition.wait(lock, [this] { 
                    return stop.load() || !tasks.empty(); 
                });
                
                // Exit if shutting down and no more tasks
                if (stop.load() && tasks.empty()) {
                    return;
                }
                
                // Get task from queue
                if (!tasks.empty()) {
                    // MOVE SEMANTICS EXPLANATION:
                    // std::move(tasks.front()) transfers ownership of the task
                    // The front element becomes "moved-from" (valid but unspecified state)
                    // tasks.pop() then removes this moved-from element safely
                    // This avoids unnecessary copying of the std::function object
                    task = std::move(tasks.front());
                    tasks.pop(); // Safe to call - removes the moved-from element
                }
            }
            
            // Execute task outside critical section
            if (task) {
                task();
            }
        }
    }

public:
    // Constructor: create thread pool with specified number of threads
    explicit ThreadPool(size_t threads = std::thread::hardware_concurrency()) {
        // Method 1: Using lambda (current approach)
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this] { worker_thread(); });
        }
        
        // Method 2: Using member function pointer (alternative approach)
        // This would also work but is less flexible:
        // for (size_t i = 0; i < threads; ++i) {
        //     workers.emplace_back(&ThreadPool::worker_thread, this);
        // }
    }

    // Destructor: automatically shutdown the thread pool
    ~ThreadPool() {
        shutdown();
    }

    // Delete copy constructor and assignment operator
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    // Move constructor and assignment operator
    ThreadPool(ThreadPool&& other) noexcept 
        : workers(std::move(other.workers))
        , tasks(std::move(other.tasks))
        , stop(other.stop.load()) {
        other.stop = true;
    }

    ThreadPool& operator=(ThreadPool&& other) noexcept {
        if (this != &other) {
            shutdown();
            workers = std::move(other.workers);
            tasks = std::move(other.tasks);
            stop = other.stop.load();
            other.stop = true;
        }
        return *this;
    }

    // Submit a task without return value (fire and forget)
    // TEMPLATE PARAMETER FORWARDING EXPLANATION:
    template<class F, class... Args>
    void enqueue(F&& f, Args&&... args) {
        // WHY MUTABLE AND FORWARDING EXPLANATION:
        // 1. We use std::forward<F>(f) to preserve the value category of f
        // 2. We use args... (not std::forward<Args>(args)...) because:
        //    - Once captured, args are lvalues inside the lambda
        //    - We want to pass them by value to f(), not by reference
        //    - Perfect forwarding is only needed at capture time, not at call time
        // 3. We use 'mutable' because:
        //    - Lambda captures are const by default
        //    - If f or args are move-only types, we need to move them when calling f
        //    - 'mutable' allows modification of captured variables
        
        auto task = [f = std::forward<F>(f), args...]() mutable {
            // Here we call f with the captured arguments
            // args... passes the captured values (not forwarded references)
            f(args...);
        };
        
        // Add task to queue
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            
            if (stop.load()) {
                throw std::runtime_error("Cannot enqueue task to stopped ThreadPool");
            }
            
            tasks.emplace(std::move(task));
        }
        
        condition.notify_one();
    }

    // Get number of worker threads
    size_t size() const {
        return workers.size();
    }

    // Get number of pending tasks
    size_t pending_tasks() const {
        std::lock_guard<std::mutex> lock(queue_mutex);
        return tasks.size();
    }

    // Check if thread pool is stopped
    bool is_stopped() const {
        return stop.load();
    }

    // Graceful shutdown: finish current tasks, ignore queued ones
    void shutdown() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if (stop.load()) return; // Already stopped
            stop = true;
        }
        
        // Wake up all threads
        condition.notify_all();
        
        // Wait for all threads to finish
        for (std::thread& worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
        
        workers.clear();
    }

    // Emergency shutdown: stop immediately, abandon all tasks
    void force_shutdown() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if (stop.load()) return;
            stop = true;
            
            // Clear all pending tasks
            std::queue<std::function<void()>> empty;
            tasks.swap(empty);
        }
        
        condition.notify_all();
        
        for (std::thread& worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
        
        workers.clear();
    }
};

// Example usage and demonstration
void demonstrate_thread_pool() {
    std::cout << "=== Thread Pool Demonstration ===\n\n";
    
    // Create thread pool with 4 threads
    ThreadPool pool(4);
    std::cout << "Created thread pool with " << pool.size() << " threads\n\n";
    
    // Example 1: Simple submit without return values
    std::cout << "1. Using simplified submit function:\n";
    
    pool.submit([]() {
        std::cout << "Simple task running on thread " 
                  << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    });
    
    pool.submit([](){ 
        std::cout << "Another simple task completed\n";
    });
    
    // Wait for tasks to complete
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout << std::endl;
    
    // Example 2: Submit tasks with return values using the advanced version
    std::cout << "2. Using advanced submit with futures:\n";
    
    auto future1 = pool.submit_with_future([](int x, int y) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return x + y;
    }, 10, 20);
    
    auto future2 = pool.submit_with_future([](const std::string& msg) {
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        return "Processed: " + msg;
    }, std::string("Hello World"));
    
    // Get results
    std::cout << "Result 1: " << future1.get() << std::endl;
    std::cout << "Result 2: " << future2.get() << std::endl;
    std::cout << std::endl;
    
    // Example 2: Fire-and-forget tasks
    std::cout << "2. Enqueueing fire-and-forget tasks:\n";
    
    for (int i = 0; i < 5; ++i) {
        pool.enqueue([i]() {
            std::cout << "Task " << i << " running on thread " 
                      << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        });
    }
}

int main() {
    demonstrate_thread_pool();
    return 0;
}