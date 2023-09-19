#include <iostream>

void foo(char* ptr)
{
    std::cout << "foo(char*)" << std::endl;
}

void foo(int i)
{
    std::cout << "foo(int)" << std::endl;
}

int main()
{
    // Call foo(char*)
    foo(nullptr);

    // Call foo(int)
    foo(NULL);

    return 0;
}
