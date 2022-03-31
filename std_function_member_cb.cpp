// going to use std::function as callback to object member function
#include <iostream>
#include <functional>
#include <typeinfo>

typedef std::function<void()> lambda_cb_t;
typedef void (*void_cb_t)();

struct S2;

struct S1
{
    int         n{0};
    lambda_cb_t get_lambda_cb()
    {
        n                    = 1954;
        const auto lambda_cb = [this]() {
            std::cout << "hello world\n";
            std::cout << this->n << "\n";
        };
        void (*lambda_cb2)() = []() {
            std::cout << "hello world\n";
            std::cout << 1969 << "\n";
        };
        std::cout << typeid(lambda_cb).name() << "\n";
        std::cout << typeid(lambda_cb2).name() << "\n";
        lambda_cb2();
        return lambda_cb;
    }
};

int main()
{
    lambda_cb_t lambda_cb;
    S1          s1;
    lambda_cb = s1.get_lambda_cb();
    lambda_cb();
}
