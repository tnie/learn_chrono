
#include <experimental\coroutine>

struct Task
{
    struct promise_type {
        auto get_return_object() { return Task{}; }
        auto initial_suspend() { return std::experimental::suspend_never{}; }
        auto final_suspend() { return std::experimental::suspend_never{}; }
        void unhandled_exception() { std::terminate(); }
        void return_void() {}
    };
};