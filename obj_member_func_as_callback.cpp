// filename: obj_member_func_as_callback.cpp
// Callback queue of object member functions
#include <iostream>
#include <deque>
using std::cout;

struct S {
    typedef void (S::*MemberFuncPtr)();
    void h1() { cout << "hello1\n"; }
    void h2() { cout << "hello2\n"; }
    void h3() { cout << "hello3\n"; }
} s;

struct CallbackViaObject {
    struct S *obj_ptr;
    S::MemberFuncPtr func_ptr;
};

std::deque<CallbackViaObject> queue;

int main() {
    S *pS = &s;
    queue.push_back(CallbackViaObject{pS, &S::h1});
    queue.push_back(CallbackViaObject{pS, &S::h2});
    queue.push_back(CallbackViaObject{pS, &S::h3});

    for (auto &cb : queue) ((cb.obj_ptr)->*(cb.func_ptr))();
    return 0;
}
