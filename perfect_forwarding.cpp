// std::forward
// perfect forwarding
#include <iostream>

void g(int& x) {std::cout << "int& " << x << "\n";}
void g(int&& x) {std::cout << "int&& " << x << "\n";}

template<typename T>
void f(T&& x)
{
    g(std::forward<T>(x));
    // std::cout << "T&& x\n";
}

int main() {
    int z{1969};
    f(z);
    f(1954);
}
