#include <iostream>
#include <string>
#include <vector>

struct A {
    std::string s;
    A(std::string str) : s(std::move(str)) { std::cout << " constructed\n"; }
    A(const A& o) : s(o.s) { std::cout << " copy constructed\n"; }
    A(A&& o) : s(std::move(o.s)) { std::cout << " move constructed\n"; }
    A& operator=(const A& other) {
        s = other.s;
        std::cout << " copy assigned\n";
        return *this;
    }
    A& operator=(A&& other) {
        s = std::move(other.s);
        std::cout << " move assigned\n";
        return *this;
    }
};

int main()
{
    std::vector<A> container;
    // reserve enough place so vector does not have to resize
    container.reserve(10);
    std::cout << "construct 2 times A:\n";
    A two{ "two" };
    A three{ "three" };

    std::cout << "emplace:\n";
    container.emplace(container.end(), "one");

    std::cout << "///////////////////////////////////  " << std::endl;
    std::cout << "emplace with A&:\n";
    container.emplace(container.end(), two);

    std::cout << "///////////////////////////////////  " << std::endl;
    std::cout << "emplace with A&&:\n";
    container.emplace(container.end(), std::move(three));

    std::cout << "///////////////////////////////////  " << std::endl;
    std::cout << "push_back :\n";
    container.push_back(three);  // three is not valid here, is used just for test

    std::cout << "///////////////////////////////////  " << std::endl;
    std::cout << "push_back with std::move:\n";
    container.push_back(std::move(three)); // three is not valid here, is used just for test

    std::cout << '\n';
}