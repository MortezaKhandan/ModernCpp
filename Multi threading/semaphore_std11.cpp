/*
The key difference between a semaphore and a mutex is how they're used to achieve mutual exclusion. A semaphore can be used to allow a certain number of threads or 
processes to access a shared resource or critical section simultaneously. For example, if a semaphore has a maximum value of 5, up to 5 threads or processes can access
 the shared resource or critical section at the same time.
This can be useful in scenarios where it's acceptable for multiple threads or processes to access the shared resource or critical section concurrently, up to a certain limit.

A mutex, on the other hand, is typically used to ensure exclusive access to a shared resource or critical section among only one thread or process at a time.
In other words, a mutex is designed to allow only one thread or process to access the shared resource or critical section at any given time, and all other threads
 or processes must wait until the mutex is released before they can access the resource.

So in summary, both a semaphore and a mutex can be used to provide mutual exclusion, but a semaphore allows a certain number of threads or processes to access
a shared resource or critical section simultaneously, while a mutex allows only one thread or process to access the shared resource or critical section at a time.
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    Semaphore(int count = 0)
        : count_(count) {}

    void notify() {
        std::unique_lock<std::mutex> lock(mutex_);
        ++count_;
        cv_.notify_one();
    }

    void wait() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (count_ == 0) {
            cv_.wait(lock);
        }
        --count_;
    }

private:
    std::mutex mutex_;
    std::condition_variable cv_;
    int count_;
};

Semaphore sem(3);

void thread_func(int thread_num) {
    sem.wait();
    std::cout << "Thread " << thread_num << " entered the critical section" << std::endl;
    // Do some work...
    std::cout << "Thread " << thread_num << " exited the critical section" << std::endl;
    sem.notify();
}

int main() {
    std::thread t1(thread_func, 1);
    std::thread t2(thread_func, 2);
    std::thread t3(thread_func, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
