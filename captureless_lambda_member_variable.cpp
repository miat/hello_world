// Been trying to figure out how to create unique captureless lambda (function pointer)
// as class variable
//
#include <iostream>
using namespace std;
typedef void (*FuncPtr)();

struct S {
    FuncPtr fp;
    S(FuncPtr init) : fp(init) { }
    void tickle_me() { (*fp)(); }
};

// this macro creates a unique, captureless lambda as a member variable in the object
// declaration
#define MY_STRUCT(pin) S([]() { cout << "hello pin: " << pin << endl; })

int main() {
    S s1 = MY_STRUCT(1954);
    s1.tickle_me();

    S s2 = MY_STRUCT(1969);
    s2.tickle_me();
}
