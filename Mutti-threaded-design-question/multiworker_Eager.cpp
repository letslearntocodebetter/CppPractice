
#include <functional>
#include <mutex>
#include <memory>

using func_t = std::function<void()>;

/* This already exists, and is provided, but we cannot change it. */
class worker {
public:
    // constructor
    // - work_fn takes no arguments
    // - work_fn will never raise an exception
    worker(func_t work_fn);

    // start the work, call back when done
    // - start returns quickly (does not wait for work_fn to complete)
    // - when all of the work is done (i.e. when work_fn is done) the callback_fn is run
    void start(func_t callback_fn);
};

/* Eager execution implementation of multi_worker with simplified counter */
class multi_worker {
private:
    int in_flight;  // Tracks the number of operations in progress
    func_t callback_f;
    std::mutex lock;
    bool callback_set;

    // Our callback function that will be passed to each worker
    void notify() {
        std::lock_guard<std::mutex> guard(lock);
        in_flight--;
        
        // If callback is set and no operations are in flight, call the callback
        if (callback_set && in_flight == 0) {
            callback_f();
        }
    }

public:
    multi_worker() : in_flight(0), callback_set(false) {
    }

    // Adds and immediately starts a piece of work
    void add_work(func_t work_fn) {
        std::lock_guard<std::mutex> guard(lock);
        
        // Create and start the worker immediately
        std::unique_ptr<worker> w = std::make_unique<worker>(work_fn);
        in_flight++;
        
        // Start the worker with our notify method as the callback
        w->start([this]() { this->notify(); });
        
        // Note: we don't need to store the worker since it's already started
        // The worker will be cleaned up automatically when it completes
    }
  
    // Sets up the callback that will be triggered when all work completes
    void start(func_t callback_fn) {
        std::lock_guard<std::mutex> guard(lock);
        callback_f = callback_fn;
        callback_set = true;
        
        // If no operations are in flight, call the callback immediately
        if (in_flight == 0) {
            callback_f();
        }
    }
};


// This implementation simplifies the tracking by:

// 1. Using a single `in_flight` counter instead of separate `started` and `finished` variables
// 2. Incrementing the counter when work is added and decrementing it when work completes
// 3. Triggering the callback when `in_flight` reaches zero (and callback is set)

// The logic is now cleaner and more intuitive:
// - When we add work: increment `in_flight`
// - When work completes: decrement `in_flight`
// - When `in_flight` reaches 0 and we have a callback: call it

// This maintains all the required functionality while making the code more concise and easier to reason about.