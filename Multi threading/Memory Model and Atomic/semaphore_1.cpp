#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    Semaphore(int count = 0) : count_(count) {}

    void acquire() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (count_ == 0) {
            condition_.wait(lock);
        }
        --count_;
    }

    void release() {
        std::lock_guard<std::mutex> lock(mutex_);
        ++count_;
        condition_.notify_one();
    }

private:
    int count_;
    std::mutex mutex_;
    std::condition_variable condition_;
};
