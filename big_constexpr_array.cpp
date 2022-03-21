//Creating N-element constexpr array in C++
//(source: https://www.educative.io/edpresso/how-to-create-an-n-element-constexpr-array-in-cpp)

#include <iostream>

template <int size>
struct BigConstArray {
    int m_big_array[size];

    constexpr BigConstArray() : m_big_array() {
        for (int n=0; n<size; ++n) m_big_array[n] = n;
    }

    const int& operator[](std::size_t idx) const {return m_big_array[idx];}
};
const int ARRAY_SIZE=100;

BigConstArray<ARRAY_SIZE> big_const_array;

int main () {

    for(int i; i < ARRAY_SIZE; ++i)
    std::cout << big_const_array[i] << std::endl;
    return 69;
}
