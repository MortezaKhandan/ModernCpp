
/*
Since we only care about the final value of the counter, we use the std::atomic<int>::load() method with the same memory
order to retrieve the finalvalue and print it to the console.

Note that using std::memory_order_relaxed in this example is sufficient because we don't care about the exact order in 
which the increments happen between the threads. If we needed to ensure that the increments happen in a specific order,
we would need to use a stronger memory order, such as std::memory_order_seq_cst.
*/

/* sufficient use*/
#include <atomic>
#include <thread>

std::atomic<int> counter(0);

void increment_counter() {
    for (int i = 0; i < 1000000; ++i) {
        counter.fetch_add(1, std::memory_order_relaxed);
    }
}

int main() {
    std::thread t1(increment_counter);
    std::thread t2(increment_counter);

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << counter.load(std::memory_order_relaxed) << std::endl;

    return 0;
}



/* insufficient use*/

#include <atomic>
#include <thread>

std::atomic<int> counter(0);

void increment_counter() {
    for (int i = 0; i < 1000000; ++i) {
        counter.fetch_add(1, std::memory_order_relaxed);
    }
}

void decrement_counter() {
    for (int i = 0; i < 1000000; ++i) {
        counter.fetch_sub(1, std::memory_order_relaxed);
    }
}

int main() {
    std::thread t1(increment_counter);
    std::thread t2(decrement_counter);

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << counter.load(std::memory_order_relaxed) << std::endl;

    return 0;
}

/* 

The problem with using std::memory_order_relaxed in this way is that it does not provide any synchronization or ordering guarantees between the threads.
This means that it's possible for the threads to perform their operations out of order, leading to a race condition and unpredictable results.

In particular, because both threads are using std::memory_order_relaxed, the operations can be reordered in any way, which can lead to a situation where
the final value of the counter is not what we expect.

To fix this, we need to use a stronger memory order, such as std::memory_order_seq_cst, which provides total ordering of memory operations across all threads.
This ensures that the increments and decrements are executed in a globally consistent order, preventing race conditions and ensuring correct behavior.

////////
It is true that atomic operations provide some level of thread-safety and reduce the likelihood of race conditions, but they do not completely eliminate the possibility
of race conditions.

Race conditions can still occur with atomic operations if they are not used correctly, for example, if the memory order used is insufficient for the specific use case or
if the shared data is accessed by multiple threads without proper synchronization.

In the case of using std::memory_order_relaxed, there are no ordering or synchronization guarantees, which can lead to race conditions if the threads perform their operations
out of order.

So while using atomic operations can help to reduce the likelihood of race conditions, it is still important to use the appropriate memory order and proper synchronization
mechanisms to ensure correct behavior in multi-threaded programs.

*/