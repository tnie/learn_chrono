#pragma once

#include <chrono>
#include <thread>
#include <future>

int blocking_recurse_fib(int n)
{
    if (n < 2) {
        return n;
    }
    return blocking_recurse_fib(n - 1) + blocking_recurse_fib(n - 2);
}

int blocking_fib(int n)
{
    if (n < 2) {
        return n;
    }
    auto fib0 = 0;
    auto fib1 = 1;
    for (size_t i = 2; i < n; i++) {
        //{fib0, fib1} = { fib1, (fib0 + fib1) };
        auto temp = fib0 + fib1;
        fib0 = fib1;
        fib1 = temp;
    }
    return (fib0 + fib1);
}

int async_rescurse_fib(int n)
{
    if (n < 2) {
        return n;
    }
    auto f = std::async(std::launch::async, [n]() {
        return async_rescurse_fib(n - 1);
    });
    auto y = async_rescurse_fib(n - 2);
    return y + f.get();
}

std::future<int> async_fib(int n)
{
    if (n<2) {
        co_return n;
    }
    auto fib0 = 0;
    auto fib1 = 1;
    for (size_t i = 2; i < n; i++)
    {
        //{fib0, fib1} = { fib1, (fib0 + fib1) };
        auto temp = co_await std::async(std::launch::async,
            [=]() {
            return fib0 + fib1;
        });
        fib0 = fib1;
        fib1 = temp;
    }
    co_return (fib0 + fib1);
}
