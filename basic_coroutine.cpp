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
    void await_resume() { }

    // return_value
};

struct ReturnObject : std::coroutine_handle<> {
    std::coroutine_handle<> m_handle;
    struct promise_type {
        using Handle = std::coroutine_handle<promise_type>;

        ReturnObject get_return_object() { return ReturnObject{Handle::from_promise(*this)}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void(){};
        void unhandled_exception() { }
    };
    explicit ReturnObject(promise_type::Handle coro) : m_handle(coro) { }
    ReturnObject(const ReturnObject &) = delete;
    ReturnObject &operator=(const ReturnObject &) = delete;
    ReturnObject(ReturnObject &&t) noexcept : m_handle(t.m_handle) { t.m_handle = {}; }
    ReturnObject &operator=(ReturnObject &&t) noexcept {
        if (this == &t) return *this;
        if (m_handle) m_handle.destroy();
        m_handle = t.m_handle;
        t.m_handle = {};
        return *this;
    }
    void resume() { m_handle.resume(); }
    void destroy() { m_handle.destroy(); }
};

ReturnObject counter() {
    Awaiter a;
    for (int i = 0;; ++i) {
        co_await a;
        cout << "counter: " << i << endl;
    }
    co_return;
}

int main() {
    auto handle = counter();
    for (int i = 0; i < 3; ++i) {
        std::cout << "In main1 function\n";
        handle.resume();
    }
    handle.destroy();
}
