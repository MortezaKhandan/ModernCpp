
/*
In this example, we have a producer thread that creates a new Data object and stores its address in an
std::atomic<Data*> variable data_ptr with the std::memory_order_release memory order. We also have a 
consumer thread that loads the pointer from data_ptr with the std::memory_order_consume memory order,
and then accesses the value member of the Data object.

The std::memory_order_consume memory order is used to ensure that the consumer thread always sees the most
recent version of the Data object, even if it is modified by another thread. This is achieved by requiring
that the consumer thread perform a dependency chain from the data_ptr load to the value member access.

In this case, the padding array is used to ensure that the Data object is large enough to span multiple cache
lines, which helps to enforce the required dependency chain and prevent data races.

Note that std::memory_order_consume is a relatively weak memory order and may not be supported on all platforms.
In general, it should be used with caution and only when absolutely necessary, as stronger memory orders such as
std::memory_order_acquire and std::memory_order_seq_cst may provide better performance and stronger guarantees of
correctness.

*/
 

// sufficient use 

#include <atomic>
#include <thread>

struct Data {
    int value;
    int padding[7];
};

std::atomic<Data*> data_ptr;

void consume_data() {
    Data* ptr = data_ptr.load(std::memory_order_consume);
    int value = ptr->value;
    // do something with the value
}

void produce_data() {
    Data* ptr = new Data{42, {0, 0, 0, 0, 0, 0, 0}};
    data_ptr.store(ptr, std::memory_order_release);
}

int main() {
    std::thread t1(consume_data);
    std::thread t2(produce_data);

    t1.join();
    t2.join();

    return 0;
}

// insufficient use 
