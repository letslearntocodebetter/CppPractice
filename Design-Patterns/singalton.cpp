// first implementation  - thread non safe

class Singleton 
{
    public: 
    static Singleton* getInstance() {
        if (!instance) {
            instance = new Singleton();
        }
        return instance;

    }
    Singleton(const Singleton&) = delete;
    Singleton& operator = (const Singleton&) = delete;

    Singleton(Singleton&& other) = delete;
    Singleton& operator = (Singleton && other) = delete;
    
    private:
    Singlton() = default;
    static Singleton *instance;
};

// mutlithread version

class Singleton 
{
    public: 
    static Singleton* getInstance() {
        
        std::lock<std::mutex> lock{lock_};
        if (!instance) {
            instance = new Singleton();
        } else {
            lock.unlock();
        }
        return instance;

    }
    Singleton(const Singleton&) = delete;
    Singleton& operator = (const Singleton&) = delete;

    Singleton(Singleton&& other) = delete;
    Singleton& operator = (Singleton && other) = delete;
    
    private:
    Singlton() = default;
    static Singleton *instance_;
    static std::mutex lock_;
};

// scott mayer version of Singleton, modern c++
class Singleton 
{
    public: 
    static Singleton& getInstance() {
        static Singleton instance;
        return instance; 

    }
    Singleton(const Singleton&) = delete;
    Singleton& operator = (const Singleton&) = delete;

    Singleton(Singleton&& other) = delete;
    Singleton& operator = (Singleton && other) = delete;
    
    private:
    Singlton() = default;
};

#include <iostream>
#include <mutex>
// First if (!instance_) (Before Locking)
// Avoids unnecessary locking when the instance already exists.
// std::lock_guard<std::mutex> lock(lock_);
// Ensures only one thread enters initialization.
// Second if (!instance_) (After Locking)
// Prevents duplicate initialization when multiple threads check at the same time.

class Singleton {
public:
    static Singleton* getInstance() {
        if (!instance_) { // First check (avoid unnecessary locking)
            std::lock_guard<std::mutex> lock(lock_);
            if (!instance_) { // Second check (ensure only one instance is created)
                instance_ = new Singleton();
            }
        }
        return instance_;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

private:
    Singleton() { std::cout << "Singleton Instance Created!" << std::endl; }

    static Singleton* instance_;
    static std::mutex lock_;
};

// Static member definitions
Singleton* Singleton::instance_ = nullptr;
std::mutex Singleton::lock_;

// Mayer's version of Singleton
class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance; // Guaranteed thread-safe in C++11
        return instance;
    }

private:
    Singleton() { std::cout << "Singleton Instance Created!" << std::endl; }
    
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton & operator=()(const Singleton&&) noexcept = delete;
    Singleton(Singelton &&) = delete; 
};


int main() {
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();
    
    std::cout << "Both instances are the same: " << (s1 == s2) << std::endl;
    return 0;
}
