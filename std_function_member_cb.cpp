// going to use std::function as callback to object member function
#include <iostream>
#include <functional>
#include <typeinfo>

typedef std::function<void()> lambda_cb_t;

struct S1
{
    void bye() { std::cout << "bye world!\n"; }

    lambda_cb_t lambda_calls_bye()
    {
        const auto lambda = [this]() { this->bye(); };
        return lambda;
    }
};

int main()
{
    lambda_cb_t lambda_cb;
    S1          s1;

    lambda_cb = s1.lambda_calls_bye();
    lambda_cb();
}
