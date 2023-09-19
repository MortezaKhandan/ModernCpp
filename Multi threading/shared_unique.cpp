#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <shared_mutex>

std::vector<int> vec; // shared resource
std::shared_mutex vec_mutex; // mutex to protect the vector

void writer_thread() {
    // Acquire unique lock to modify the vector
    std::unique_lock<std::shared_mutex> lock(vec_mutex);
    vec.push_back(42);
    std::cout << "Writer thread: added value to the vector" << std::endl;
}

void reader_thread(int id) {
    // Acquire shared lock to read the vector
    std::shared_lock<std::shared_mutex> lock(vec_mutex);
    std::cout << "Reader thread " << id << ": ";
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Start writer thread
    std::thread writer(writer_thread);

    // Start multiple reader threads
    const int num_readers = 5;
    std::vector<std::thread> readers(num_readers);
    for (int i = 0; i < num_readers; ++i) {
        readers[i] = std::thread(reader_thread, i);
    }

    // Join all threads
    writer.join();
    for (auto& t : readers) {
        t.join();
    }

    return 0;
}
