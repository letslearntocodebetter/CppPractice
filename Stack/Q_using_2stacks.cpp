#include <iostream>
#include <stack>

template <typename T>
class QueueUsingStacks {
private:
    std::stack<T> inbox;   // for enqueue operations
    std::stack<T> outbox;  // for dequeue operations

    // Transfer elements from inbox to outbox when needed
    void transferIfNeeded() {
        if (outbox.empty()) {
            while (!inbox.empty()) {
                outbox.push(inbox.top());
                inbox.pop();
            }
        }
    }

public:
    // Add an element to the queue
    void enqueue(const T& item) {
        inbox.push(item);
    }

    // Remove and return the front element
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        
        transferIfNeeded();
        
        T frontItem = outbox.top();
        outbox.pop();
        return frontItem;
    }

    // Return the front element without removing it
    T front() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        
        transferIfNeeded();
        
        return outbox.top();
    }

    // Check if the queue is empty
    bool isEmpty() {
        return inbox.empty() && outbox.empty();
    }

    // Get the size of the queue
    size_t size() {
        return inbox.size() + outbox.size();
    }
};
