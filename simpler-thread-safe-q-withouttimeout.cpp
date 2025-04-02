// Thread-safe queue implementation
template <typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue;
    mutable std::mutex mutex;
    std::condition_variable cv;

public:
    void push(const T& item) {
        {
            std::lock_guard<std::mutex> lock(mutex);
            queue.push(item);
        }
        cv.notify_one();
    }

    void pop(T& item) {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [this] { return !queue.empty(); });
        item = queue.front();
        queue.pop();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }
};

// Global shared resources
ThreadSafeQueue<std::string> dataQueue;
std::atomic<bool> producerFinished{false};
std::shared_mutex rwMutex;

// Writer function
void writer(int numItems) {
    for (int i = 0; i < numItems; ++i) {
        std::string data = "String-" + std::to_string(i);
        dataQueue.push(data);
        {
            std::unique_lock<std::shared_mutex> writeLock(rwMutex);
            std::cout << "Writer produced: " << data << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    producerFinished = true;
    dataQueue.push("");  // Push empty string to wake up any waiting readers
}

// Reader function
void reader(int readerID) {
    while (true) {
        std::string data;
        dataQueue.pop(data);

        if (producerFinished && data.empty()) {
            break;  // Exit condition
        }

        std::shared_lock<std::shared_mutex> readLock(rwMutex);
        std::cout << "Reader " << readerID << " consumed: " << data << std::endl;
    }