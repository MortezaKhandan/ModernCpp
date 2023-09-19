#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> shared_data(0);

void writer_thread()
{
    // increment the shared data by 1
    shared_data.fetch_add(1, std::memory_order_seq_cst);
}

void reader_thread()
{
    // read the value of shared_data
    int value = shared_data.load(std::memory_order_seq_cst);
    std::cout << "The value of shared_data is " << value << std::endl;
}

int main()
{
    // start some reader threads
    std::thread reader1(reader_thread);
    std::thread reader2(reader_thread);

    // start some writer threads
    std::thread writer1(writer_thread);
    std::thread writer2(writer_thread);

    // wait for the threads to finish
    reader1.join();
    reader2.join();
    writer1.join();
    writer2.join();

    return 0;
}