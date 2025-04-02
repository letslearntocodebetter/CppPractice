#include <iostream>
#include <vector>
#include <thread>
#include <functional>

class Worker {
public:
    // Type definition for the function pointer (callback function)
    using func_t = std::function<void()>;

    // Vector to store the list of tasks
    std::vector<func_t> tasks;

    // Adds a task to be executed later
    void add_work(func_t work_f) {
        tasks.push_back(work_f);
    }

    // Start all tasks concurrently
    void start() {
        // Start all tasks in separate threads
        for (auto& task : tasks) {
            std::thread([task]() {
                task(); // Execute the work function
            }).detach(); // Detach the thread to allow parallel execution
        }
        
        // Call callback function after all work is completed (no sync, assuming single callback for simplicity)
        // A real solution would require a way to track completion and notify only once all tasks are finished.
    }
};
