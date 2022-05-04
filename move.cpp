#include <iostream>
#include <string>

int main()
{
    std::string s1{"hello world"},s2{""};
    std::cout << "s1, before: " << s1 << "\n";
    std::cout << "s2, before: " << s2 << "\n";
    s2 = std::move(s1);
    std::cout << "s1, after: " << s1 << "\n";
    std::cout << "s2, after: " << s2 << "\n";
    return 0;
}
