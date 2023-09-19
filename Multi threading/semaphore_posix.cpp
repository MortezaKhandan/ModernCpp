
#include <iostream>
#include <thread>
#include <semaphore.h>

// Define a semaphore with an initial value of 3
sem_t sem;

void thread_func(int thread_num) {
  // Wait on the semaphore
  sem_wait(&sem);
  
  // Critical section
  std::cout << "Thread " << thread_num << " entered the critical section" << std::endl;
  // Do some work...
  std::cout << "Thread " << thread_num << " exited the critical section" << std::endl;
  
  // Signal the semaphore
  sem_post(&sem);
}

int main() {
  // Initialize the semaphore
  sem_init(&sem, 0, 3);
  
  // Create three threads
  std::thread t1(thread_func, 1);
  std::thread t2(thread_func, 2);
  std::thread t3(thread_func, 3);
  
  // Wait for the threads to finish
  t1.join();
  t2.join();
  t3.join();
  
  // Destroy the semaphore
  sem_destroy(&sem);
  
  return 0;
}
