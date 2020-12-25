
#include <experimental\coroutine>

//https://lewissbaker.github.io/2018/09/05/understanding-the-promise-type
//How the compiler chooses the promise type?
//by looking for a nested promise_type typedef defined on the return-type.
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