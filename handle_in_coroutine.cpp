#include <iostream>
#include <coroutine>
using namespace std;

struct ReturnObject2 {
    struct promise_type {
        ReturnObject2 get_return_object() {
            return {// Uses C++20 designated initializer syntax
                    .h_ = std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void unhandled_exception() { }
    };

    std::coroutine_handle<promise_type> h_;
    operator std::coroutine_handle<promise_type>() const {
        cout << "operator<promise_type>()\n";
        return h_;
    }
    // A coroutine_handle<promise_type> converts to coroutine_handle<>
    operator std::coroutine_handle<>() const {
        cout << "operator<>()\n";
        return h_;
    }

    // ReturnObject2() { }
};

ReturnObject2 counter2() {
    for (unsigned i = 0;; ++i) {
        std::cout << "counter2: " << i << std::endl;
        co_await std::suspend_always{};
    }
}

int main() {
    cout << "main()\n";
    std::coroutine_handle<> h = counter2();
    for (int i = 0; i < 3; ++i) {
        std::cout << "In main function\n";
        h();
    }
    h.resume();
    h.resume();
    h();
    h.destroy();
}
