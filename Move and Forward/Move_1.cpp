
/*
This move function takes a single argument of type T&&, which can be an lvalue reference or an rvalue reference.
The remove_reference type trait is used to strip the reference from the type T, and the && at the end of the return type is used to create an rvalue reference.
The static_cast expression inside the function is used to convert the argument to an rvalue reference, which enables move semantics.
The noexcept specifier indicates that the function is declared to be noexcept, which means that it guarantees not to throw any exceptions.
This custom move function is equivalent to the std::move function provided by the C++ standard library, and can be used to enable move semantics for objects that support them.
*/
#include <iostream>

template<typename T>
typename std::remove_reference<T>::type&& move(T&& arg) noexcept {
    return static_cast<typename std::remove_reference<T>::type&&>(arg);
}
