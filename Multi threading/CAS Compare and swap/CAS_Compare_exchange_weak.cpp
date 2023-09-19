/*
The main difference between compare_exchange_strong and compare_exchange_weak is that compare_exchange_weak may fail spuriously,
even if the comparison is true1. This means that it may return false and not update the atomic object even if the expected value
matches the current value.
The reason why there is a weak version is that on some architectures, it is cheaper than the strong version1. The weak version can
be implemented using a load-linked/store-conditional (LL/SC) instruction pair, which may fail due to various reasons such as inter-
rupts or cache misses1.
The strong version guarantees that it will only fail if the comparison is false. It may require more complex instructions or addit-
ional loops to ensure this guarantee1.
In general, you should use compare_exchange_weak when you have a retry loop around it and you don’t care about spurious failures.
You should use compare_exchange_strong when you need a reliable result or when you don’t have a retry loop.
*/

std::atomic<bool> locked(false); // initialize locked to false

void lock() {
  bool expected = false; // set expected to false
  while (!locked.compare_exchange_weak(expected, true)) { // try to atomically set locked to true if it is false
    expected = false; // reset expected to false if compare_exchange_weak failed
  }
}

void unlock() {
  locked.store(false); // set locked to false
}

/*
This code uses compare_exchange_weak in a loop to try to acquire the lock by setting the locked variable to true.
If the variable is already true, it means that another thread has acquired the lock and compare_exchange_weak will
fail and return false. It will also update the expected variable to true, so we need to reset it back to false before retrying.

If we use compare_exchange_strong instead of compare_exchange_weak, we don’t need to reset the expected variable
because it will not fail spuriously. However, on some architectures, compare_exchange_strong may be more expensive
than compare_exchange_weak.
*/