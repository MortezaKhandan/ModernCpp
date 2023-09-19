

/*
In this example, we have a shared variable counter that is accessed by multiple threads using std::atomic<int>. In the main function,
we start two threads and then increment the value of counter to 10 using std::atomic::store with std::memory_order_release. This memory
order guarantees that any memory operations performed by the current thread after the store operation are visible to the other threads
that perform load operations from the same memory location.

Each thread executes thread_func(), which loads the value of counter using std::atomic::load with std::memory_order_acquire. This memory
order guarantees that any memory operations performed by the current thread before the load operation are visible to the other threads 
that perform store operations to the same memory location.

By using std::memory_order_acquire and std::memory_order_release, we ensure that any memory operations performed by the other threads before
the store operation to counter are visible to the current thread when it loads the value of counter. This prevents race conditions and ensures
that the computation performed by the current thread using the loaded value is consistent with the current state of the shared variable.

*/

#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> counter(0);

void thread_func()
{
    int val = counter.load(std::memory_order_acquire);
    // perform some computation using val
    for(int i = 0; i < val; i++) {
        std::cout << "Thread ID " << std::this_thread::get_id() << ": " << i << std::endl;
    }
}

int main()
{
    // start two threads
    std::thread t1(thread_func);
    std::thread t2(thread_func);

    // increment the counter
    counter.store(10, std::memory_order_release);

    // wait for the threads to finish
    t1.join();
    t2.join();

    return 0;
}
