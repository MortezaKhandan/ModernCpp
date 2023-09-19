/*
just add increament the value which can be done with bothe CAS and member function
 of std::atomic<int> such as counter++; andcounter.fetch_add(1);  
 pay attention that the ++counter is not member function of automic.
*/

std::atomic<int> counter(0); // initialize counter to 0

void increment_counter() {
  int expected = counter.load(); // load the current value of counter
  int desired = expected + 1; // calculate the desired value of counter
  while (!counter.compare_exchange_strong(expected, desired)) { // try to update counter atomically
    // if compare_exchange_strong returns false, it means another thread has changed the value of counter
    // and we need to retry with the new value
    expected = counter.load(); // load the new value of counter
    desired = expected + 1; // calculate the new desired value of counter
  }
  // if compare_exchange_strong returns true, it means we have successfully updated counter
}

/* same as above with member function of automic */

std::atomic<int> counter(0); // initialize counter to 0

void increment_counter() {
  counter.fetch_add(1); // atomically increment counter by 1
  // or
  counter++; // same as above
}



/***********************************************************************************************************
The reason we may want to use compare_exchange_strong is that it is more general and flexible than fetch_add.
Fetch_add can only perform a simple addition operation on the atomic object, but compare_exchange_strong can
perform any kind of modification based on the current value of the object.
For example, if we want to increment counter only if it is even, we can use compare_exchange_strong like this:
*/
std::atomic<int> counter(0); // initialize counter to 0

void increment_counter_if_even() {
  int expected = counter.load(); // load the current value of counter
  int desired;
  do {
    if (expected % 2 == 0) { // check if counter is even
      desired = expected + 1; // calculate the desired value of counter
    } else {
      desired = expected; // keep the same value of counter
    }
  } while (!counter.compare_exchange_strong(expected, desired)); // try to update counter atomically
}

/*
This way, we can implement a more complex logic on the atomic object than just adding one.
Fetch_add cannot do this kind of conditional update.
*/