#include <coroutine>
#include <iostream>
#include <cassert>
#include "am_cxx20_coroutines/module.h"

class resumable {
public:
    struct promise_type;
    using coro_handle = std::coroutine_handle<promise_type>;
    resumable(coro_handle handle) : handle_(handle) { assert(handle); }
    resumable(resumable&) = delete;
    resumable(resumable&&) = delete;
    bool resume() {
        if (not handle_.done())
            handle_.resume();
        return not handle_.done();
    }
    ~resumable() { handle_.destroy(); }
private:
    coro_handle handle_;
};

struct resumable::promise_type {
    using coro_handle = std::coroutine_handle<promise_type>;

    auto get_return_object() noexcept {
        return coro_handle::from_promise(*this);
    }

    auto initial_suspend() noexcept { return std::suspend_always(); }
    auto final_suspend() noexcept { return std::suspend_always(); }
    void return_void() noexcept {}
    void unhandled_exception() noexcept {
        std::terminate();
    }
};

resumable foo() {
    std::cout << "a" << std::endl;
    co_await std::suspend_always();
    std::cout << "b" << std::endl;
    co_await std::suspend_always();
    std::cout << "c" << std::endl;
}

void play_coroutines() {
    resumable res1 = foo();
    res1.resume();
    res1.resume();
    res1.resume();
}