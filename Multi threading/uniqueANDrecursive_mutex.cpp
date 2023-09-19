#include <iostream>
#include <thread>
#include <mutex>

std::recursive_mutex mtx;

void recursive_function(int i)
{
    std::unique_lock<std::recursive_mutex> lock(mtx);
    std::cout << "Entering function " << i << std::endl;

    if (i > 0) {
        recursive_function(i-1);
    }

    std::cout << "Exiting function " << i << std::endl;
}

int main()
{
    std::thread t1(recursive_function, 3);
    std::thread t2(recursive_function, 2);

    t1.join();
    t2.join();

    return 0;
}
