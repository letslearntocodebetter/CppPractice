#include <functional>
#include <vector>
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

/* This is what we're implementing */
class multi_worker {
private:
    std::vector<std::unique_ptr<worker>> workers;
    int started;
    int finished;
    func_t callback_f;
    std::mutex lock;
    bool started_flag;

    // Our callback function that will be passed to each worker
    void notify() {
        std::lock_guard<std::mutex> guard(lock);
        finished++;
        if (started_flag && finished == started) {
            // All workers have finished, call the user's callback
            callback_f();
        }
    }

public:
    multi_worker() : started(0), finished(0), started_flag(false) {
    }

    // No need for explicit destructor - unique_ptr will handle cleanup

    // Adds a piece of work to be done by this multiworker.
    void add_work(func_t work_fn) {
        auto w = std::make_unique<worker>(work_fn);
        workers.push_back(std::move(w));
        started++;
    }
  
    // Should behave identically to Worker start:
    // - start returns quickly (does not wait for our work to complete)
    // - when all of the work is done, the callback_fn is run exactly once
    void start(func_t callback_fn) {
        callback_f = callback_fn;
        
        std::lock_guard<std::mutex> guard(lock);
        started_flag = true;
        
        // Special case: no work added
        if (started == 0) {
            callback_f();
            return;
        }
        
        // Check if all workers have already finished
        if (finished == started) {
            callback_f();
            return;
        }
        
        // Start all workers with our notify method as the callback
        for (auto& w : workers) {
            w->start([this]() { this->notify(); });
        }
    }
};
