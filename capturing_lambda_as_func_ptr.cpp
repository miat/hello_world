// capturing_lambda_as_func_ptr.cpp
#include <stdio.h>
#include <stdlib.h>

typedef void (*callback_closure_t)(int n, void*context);

void dotimes_version2(int size, callback_closure_t fun, void *context) {
for (int i=0; i<size; ++i) fun(i, context);
}

#include <iostream>
#include <functional>
#include <typeinfo>

int main() {
    int counter = -100;
    auto callback_lambda = [&counter](int n) {printf("FUNCTOR n = %d, counter = %d \n",n,counter++);};

    typedef std::function<void(int size)> FunctionCallback2;
    auto adapter_for_lambda = [](int n, void*context) {
        FunctionCallback2 *pFunc = reinterpret_cast<FunctionCallback2 *>(context);
        (*pFunc)(n);
    };
    FunctionCallback2 callback_object = callback_lambda;

    dotimes_version2(5,adapter_for_lambda,&callback_object);
}
