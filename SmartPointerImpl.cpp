#include <iostream>
#include <utility>  // for std::move

// Custom unique pointer class
template <typename T>
class UniquePointer {
private:
    T* ptr;  // Raw pointer to the managed object

public:
    // Constructors
    explicit UniquePointer(T* p = nullptr) : ptr(p) {}

    // Destructor
    ~UniquePointer() {
        delete ptr;
    }

    // Delete copy constructor and copy assignment operator
    UniquePointer(const UniquePointer&) = delete;
    UniquePointer& operator=(const UniquePointer&) = delete;

    // Move constructor
    UniquePointer(UniquePointer&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    // Move assignment operator
    UniquePointer& operator=(UniquePointer&& other) noexcept {
        if (this != &other) {
            delete ptr;         // Release the current resource
            ptr = other.ptr;    // Transfer ownership
            other.ptr = nullptr; // Nullify the other pointer
        }
        return *this;
    }

    // Overload dereference operator
    T& operator*() const {
        return *ptr;
    }

    // Overload arrow operator
    T* operator->() const {
        return ptr;
    }

    // Get the raw pointer
    T* get() const {
        return ptr;
    }

    // Release ownership of the managed object
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // Reset the managed object
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};

// Usage example
class Test {
public:
    void show() {
        std::cout << "Test class method called" << std::endl;
    }
};

int main() {
    UniquePointer<Test> uptr(new Test());
    uptr->show();  // Access the managed object

    UniquePointer<Test> uptr2 = std::move(uptr);  // Transfer ownership
    if (!uptr.get()) {
        std::cout << "uptr is empty after move" << std::endl;
    }

    uptr2->show();  // Access the managed object

    uptr2.reset(new Test());  // Reset with a new object
    uptr2->show();  // Access the new managed object

    Test* rawPtr = uptr2.release();  // Release ownership
    if (!uptr2.get()) {
        std::cout << "uptr2 is empty after release" << std::endl;
    }
    delete rawPtr;  // Manually delete the released object

    return 0;
}
//////////////////////////////////////////////////////////////////////////////// Shared_pointer ///////////////////////////////////////////////////////
#include <iostream>
#include <utility> // for std::swap

// Custom shared pointer class
template <typename T>
class SharedPointer {
private:
    T* ptr;            // Raw pointer to the managed object
    size_t* refCount;  // Pointer to the reference count

public:
    // Constructor
    explicit SharedPointer(T* p = nullptr)
        : ptr(p), refCount(new size_t(1)) {}

    // Copy constructor
    SharedPointer(const SharedPointer& other)
        : ptr(other.ptr), refCount(other.refCount) {
        ++(*refCount);
    }

    // Move constructor
    SharedPointer(SharedPointer&& other) noexcept
        : ptr(other.ptr), refCount(other.refCount) {
        other.ptr = nullptr;
        other.refCount = nullptr;
    }

    // Copy assignment operator
    SharedPointer& operator=(const SharedPointer& other) {
      if (this != &other) { // Avoid self-assignment
          // Decrease the reference count of the current object
          if (--(*refCount) == 0) { 
              delete ptr;       // Delete the managed object if no more owners
              delete refCount;  // Delete the reference count itself
          }
      
          // Assign new values from 'other'
          ptr = other.ptr;
          refCount = other.refCount;
          ++(*refCount); // Increase the reference count for the new object
      }
      return *this;
    }

    // Move assignment operator
    SharedPointer& operator=(SharedPointer&& other) noexcept {
        if (this != &other) {
            // Decrease the reference count of the current object
            if (--(*refCount) == 0) {
                delete ptr;
                delete refCount;
            }

            // Transfer ownership from the other object
            ptr = other.ptr;
            refCount = other.refCount;
            other.ptr = nullptr;
            other.refCount = nullptr;
        }
        return *this;
    }

    // Destructor
    ~SharedPointer() {
        if (refCount && --(*refCount) == 0) {
            delete ptr;
            delete refCount;
        }
    }

    // Overload dereference operator
    T& operator*() const {
        return *ptr;
    }

    // Overload arrow operator
    T* operator->() const {
        return ptr;
    }

    // Get the raw pointer
    T* get() const {
        return ptr;
    }

    // Get the reference count
    size_t use_count() const {
        return refCount ? *refCount : 0;
    }
};

// Usage example
class Test {
public:
    void show() {
        std::cout << "Test class method called" << std::endl;
    }
};

int main() {
    SharedPointer<Test> sp1(new Test());
    {
        SharedPointer<Test> sp2 = sp1;  // Copy construction
        std::cout << "Reference count after sp2 copy: " << sp1.use_count() << std::endl;
        sp2->show();
    }
    std::cout << "Reference count after sp2 goes out of scope: " << sp1.use_count() << std::endl;

    SharedPointer<Test> sp3;
    sp3 = sp1;  // Copy assignment
    std::cout << "Reference count after sp3 assignment: " << sp1.use_count() << std::endl;
    sp3->show();

    SharedPointer<Test> sp4 = std::move(sp3);  // Move construction
    std::cout << "Reference count after sp4 move: " << sp1.use_count() << std::endl;
    if (!sp3.get()) {
        std::cout << "sp3 is empty after move" << std::endl;
    }
    sp4->show();

    return 0;
}
