/*
constexpr and const are used for different purposes, so it depends on the situation.

const is used to declare objects that are not modifiable after initialization. This means that the value of a const object cannot be changed once it has been initialized.
However, the value of a const object may not be known at compile-time.

constexpr, on the other hand, is used to declare objects or functions that can be evaluated at compile-time. This means that the value of a constexpr object or the result
of a constexpr function must be known at compile-time.

So, if you have a value that can be determined at compile-time, it is better to use constexpr instead of const. This can help improve performance and can also allow for 
more opportunities for optimization by the compiler. However, if you have a value that can only be determined at runtime, you should use const.

In general, constexpr is more powerful than const, but it has stricter requirements. It is also only available in C++11 and later versions, while const has been available
 since the early versions of C++.
*/

#include <iostream>

int main()
{
    int test;
    std::cin >> test;

    const int conttest = test;
    std::cout << conttest << std::endl;
    return 0;
}