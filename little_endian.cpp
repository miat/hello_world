#include <cstdint>
#include <iostream>
/*constexpr*/ bool is_little_endian()
{
    std::uint16_t x = 0x0001;
    auto          p = reinterpret_cast<std::uint8_t*>(&x);
    return *p != 0;
}

int main()
{
    std::cout << "This system is ";
    if (!is_little_endian()) std::cout << "not ";
    std::cout << "little endian.\n";
    return 0;
}