// A function that takes an lvalue or an rvalue and prints its type
void print(int& x) {
  std::cout << "lvalue: " << x << "\n";
}
void print(int&& x) {
  std::cout << "rvalue: " << x << "\n";
}

// A templated function that takes a forwarding reference and forwards it to print
template<typename T>
void forward_print(T&& t) {
  print(std::forward<T>(t)); // preserves the value category of t
}

int main() {
  int a = 10; // a is an lvalue
  forward_print(a); // calls print(int&), prints "lvalue: 10"
  forward_print(20); // calls print(int&&), prints "rvalue: 20"
}