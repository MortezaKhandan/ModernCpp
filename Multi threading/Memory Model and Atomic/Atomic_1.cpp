/*
Yes, atomic operations are related to hardware. Atomic operations guarantee that a particular operation (e.g., read, write, or update) will be performed atomically, without
any other thread interrupting the operation in the middle of its execution. This guarantee is typically provided by the hardware, using specialized instructions such as 
Compare-and-Swap (CAS) or Load-Linked/Store-Conditional (LL/SC), which ensure that the memory access is indivisible and isolated from concurrent accesses by other threads.

The exact mechanism used to provide atomic operations can vary depending on the architecture and platform, but it is typically implemented at the hardware level. Some 
processors may provide more efficient or more powerful atomic operations than others, depending on their design and capabilities.
*/
#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> counter{ 0 };
//int counter{0};

void increment()
{
    for ( int i = 0; i < 20; ++i )
       std::cout << "Thread_Id = " << std::this_thread::get_id() << " counter =  "  <<  counter++ << std::endl;
    
        
}

int main()
{
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Counter value: " << counter << '\n';

    return 0;
}