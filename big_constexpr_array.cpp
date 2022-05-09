//Creating N-element constexpr array in C++
//(source: https://www.educative.io/edpresso/how-to-create-an-n-element-constexpr-array-in-cpp)

#include <iostream>
#include <array>
template <int SIZE>
struct S {
    std::array<int, SIZE> arr;
    constexpr S() : arr{} {
        auto i=0;
        for (auto& e:arr) {e=i++;}
        arr[49]=1954;
        arr[50]=1969;
    }
    const int& operator[](int i) const {return arr[i];}
};
constexpr S<100> s;
int main() {
    int i;
    i = s[49];
}
