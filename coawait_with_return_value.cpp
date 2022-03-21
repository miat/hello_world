// basic_coroutine.hpp
// Coroutine handle made available to caller.
// get_return_object() to create handle from the promise
// instance.
#include <iostream>
#include <coroutine>

using namespace std;

class Awaiter {
  public:
    std::coroutine_handle<> m_handle;
    bool await_ready() { return false; }
    void await_suspend(std::coroutine_handle<> handle_) { m_handle = handle_; }
    int await_resume() { return 2001; }

    // return_value
};

struct ReturnObject {
    std::coroutine_handle<> m_handle = NULL;
    struct promise_type {
        using Handle = std::coroutine_handle<promise_type>;

        ReturnObject get_return_object() { return ReturnObject{Handle::from_promise(*this)}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void(){};
        void unhandled_exception() { }
    };

    void resume() {
        m_handle.resume();
    }
};

ReturnObject task1() {
    Awaiter a;
    int result;
    cout << "task1\n";
    result = co_await a;

    cout << result << endl;
    cout << "co_return\n";
    co_return;
}

int main() {
    auto t1 = task1();
    t1.resume();
}
