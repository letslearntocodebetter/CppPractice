#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>


void printEven() {
        while (true) {
            std::unique_lock<std::mutex> lock(mutex);
            
            // Wait until it's even's turn
            cv.wait(lock, [this] { return !isOddTurn || number > MAX; });
            
            // Check if we're still within range (while still holding the lock)
            if (number > MAX) {
                // We're done, exit the loop
                lock.unlock();
                cv.notify_one(); // Wake up the other thread so it can exit too
                break;
            }
            
            std::cout << "Even Thread: " << number << std::endl;
            number++;
            isOddTurn = true;  // Toggle to odd's turn
            
            lock.unlock();
            cv.notify_one();
        }
    }

    void printOdd() {
        while (true) {
            std::unique_lock<std::mutex> lock(mutex);
            
            // Wait until it's odd's turn
            cv.wait(lock, [this] { return isOddTurn || number > MAX; });
            
            // Check if we're still within range (while still holding the lock)
            if (number > MAX) {
                // We're done, exit the loop
                lock.unlock();
                cv.notify_one(); // Wake up the other thread so it can exit too
                break;
            }
            
            std::cout << "Odd Thread: " << number << std::endl;
            number++;
            isOddTurn = false;  // Toggle to even's turn
            
            lock.unlock();
            cv.notify_one();
        }
    }
};

class OddEvenPrinter {
private:
    int max;
    int current;
    bool isOddTurn;
    std::mutex mtx;
    std::condition_variable cv;

public:
    OddEvenPrinter(int n) : max(n), current(1), isOddTurn(true) {}

    void printOdd() {
        while (current <= max) {
            std::unique_lock<std::mutex> lock(mtx);
            
            // Wait if it's not odd's turn or we've exceeded max
            cv.wait(lock, [this]() { 
                return isOddTurn && current <= max; 
            });

            if (current <= max) {
                std::cout << "Odd Thread: " << current << std::endl;
                current++;
                isOddTurn = false;
            }

            lock.unlock();
            cv.notify_all();
        }
    }

    void printEven() {
        while (current <= max) {
            std::unique_lock<std::mutex> lock(mtx);
            
            // Wait if it's not even's turn or we've exceeded max
            cv.wait(lock, [this]() { 
                return !isOddTurn && current <= max; 
            });

            if (current <= max) {
                std::cout << "Even Thread: " << current << std::endl;
                current++;
                isOddTurn = true;
            }

            lock.unlock();
            cv.notify_all();
        }
    }
};

void threadFunction(OddEvenPrinter* printer, bool isOdd) {
    if (isOdd) {
        printer->printOdd();
    } else {
        printer->printEven();
    }
}

int main() {
    int n = 10;
    OddEvenPrinter printer(n);

    // Creating threads with pointer to object and additional parameter
    std::thread oddThread(threadFunction, &printer, true);
    std::thread evenThread(threadFunction, &printer, false);

    oddThread.join();
    evenThread.join();

    return 0;
}