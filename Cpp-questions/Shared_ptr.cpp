#include <atomic>
#include <utility>

// Thread-safe custom shared pointer class
template <typename T>
class SharedPointer {
private:
    T* ptr;                        // Raw pointer to the managed object
    std::atomic<size_t>* refCount; // Atomic reference count for thread safety

public:
    // Constructor - initializes with given pointer
    explicit SharedPointer(T* p = nullptr)
        : ptr(p), refCount(p ? new std::atomic<size_t>(1) : nullptr) {
        // Only create refCount if we have a valid pointer
        // This handles the case where SharedPointer(nullptr) is called
    }

    // Copy constructor - shares ownership with another SharedPointer
    SharedPointer(const SharedPointer& other)
        : ptr(other.ptr), refCount(other.refCount) {
        if (refCount) {
            // Atomically increment reference count - thread safe
            refCount->fetch_add(1, std::memory_order_relaxed);
        }
    }

    // Move constructor - transfers ownership from another SharedPointer
    SharedPointer(SharedPointer&& other) noexcept
        : ptr(other.ptr), refCount(other.refCount) {
        // Transfer ownership without touching reference count
        other.ptr = nullptr;
        other.refCount = nullptr;
    }

    // Copy assignment operator - changes what this SharedPointer points to
    SharedPointer& operator=(const SharedPointer& other) {
        if (this != &other) { // Avoid self-assignment
            // First, release our current resource
            release();
            
            // Then acquire the new resource
            ptr = other.ptr;
            refCount = other.refCount;
            if (refCount) {
                // Atomically increment reference count for new resource
                refCount->fetch_add(1, std::memory_order_relaxed);
            }
        }
        return *this;
    }

    // Move assignment operator - transfers ownership from another SharedPointer
    SharedPointer& operator=(SharedPointer&& other) noexcept {
        if (this != &other) {
            // Release our current resource
            release();
            
            // Transfer ownership from other without touching reference count
            ptr = other.ptr;
            refCount = other.refCount;
            other.ptr = nullptr;
            other.refCount = nullptr;
        }
        return *this;
    }

    // Destructor - releases ownership and potentially deletes the object
    ~SharedPointer() {
        release();
    }

    // Dereference operator - access the managed object
    T& operator*() const {
        return *ptr; // In production code, you'd want to check ptr != nullptr
    }

    // Arrow operator - access members of the managed object
    T* operator->() const {
        return ptr;
    }

    // Get the raw pointer without transferring ownership
    T* get() const {
        return ptr;
    }

    // Get current reference count (for debugging/monitoring)
    size_t use_count() const {
        return refCount ? refCount->load(std::memory_order_relaxed) : 0;
    }

    // Check if this is the only owner
    bool unique() const {
        return use_count() == 1;
    }

    // Reset to manage a different object (or nullptr)
    void reset(T* p = nullptr) {
        if (p != ptr) {
            release(); // Release current resource
            ptr = p;
            refCount = p ? new std::atomic<size_t>(1) : nullptr;
        }
    }

private:
    // Helper function to release current resource
    void release() {
        if (refCount) {
            // Atomically decrement and get the previous value
            // This is crucial: we need to know what the count was BEFORE decrementing
            size_t prevCount = refCount->fetch_sub(1, std::memory_order_acq_rel);
            
            if (prevCount == 1) {
                // We were the last owner, safe to delete
                // No other thread can have a reference at this point
                delete ptr;
                delete refCount;
            }
        }
        ptr = nullptr;
        refCount = nullptr;
    }
};

// Example usage and test
#include <iostream>
#include <thread>
#include <vector>

class TestClass {
public:
    int value;
    TestClass(int v) : value(v) {
        std::cout << "TestClass(" << v << ") created\n";
    }
    ~TestClass() {
        std::cout << "TestClass(" << value << ") destroyed\n";
    }
};

// Function to test thread safety
void threadTest(SharedPointer<TestClass> sp, int threadId) {
    for (int i = 0; i < 1000; ++i) {
        // Create copies to stress test the reference counting
        SharedPointer<TestClass> copy1 = sp;
        SharedPointer<TestClass> copy2 = copy1;
        // Copies will be destroyed when going out of scope
    }
    std::cout << "Thread " << threadId << " finished, ref count: " << sp.use_count() << "\n";
}

int main() {
    // Basic usage example
    SharedPointer<TestClass> sp1(new TestClass(42));
    std::cout << "Initial ref count: " << sp1.use_count() << "\n";
    
    {
        SharedPointer<TestClass> sp2 = sp1; // Copy
        std::cout << "After copy: " << sp1.use_count() << "\n";
        
        SharedPointer<TestClass> sp3 = std::move(sp2); // Move
        std::cout << "After move: " << sp1.use_count() << "\n";
    } // sp2 and sp3 destroyed here
    
    std::cout << "After scope exit: " << sp1.use_count() << "\n";
    
    // Thread safety test
    std::cout << "\nTesting thread safety...\n";
    std::vector<std::thread> threads;
    
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back(threadTest, sp1, i);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "Final ref count: " << sp1.use_count() << "\n";
    
    return 0;
}
