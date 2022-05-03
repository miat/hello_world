#include <iostream>

struct S 
{
    int s1 = 0;
} s;

template<class Os>
Os& operator<<(Os& os,S s)
{
    os << s.s1;
    return os;
}

int main() {
    s.s1=1969;
    std::cout << s << "\n";
    return 0;
}
