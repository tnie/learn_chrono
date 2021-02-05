#pragma once

#include <chrono>
#include <thread>
using namespace std::chrono_literals;
namespace sync
{
    /// <summary>
    /// F[0]=0, F[1]=1, F[n] = F[n-1] + F[n-2]
    /// </summary>
    /// <param name="n"></param>
    /// <returns>F[n]</returns>
    int fib(int n)
    {
#ifdef __DELAY_
        std::this_thread::sleep_for(100ms);
#endif
        if (n < 2)
        {
            return n;
        }
        return fib(n - 1) + fib(n - 2);
    }

    int fib2(int n)
    {
        if (n < 2)
        {
            return n;
        }
        auto fib0 = 0;
        auto fib1 = 1;
        for (size_t i = 2; i < n; i++)
        {
            //{fib0, fib1} = { fib1, (fib0 + fib1) };
            auto temp = fib0 + fib1;
            fib0 = fib1;
            fib1 = temp;
        }
        return (fib0 + fib1);
    }
}



#include <future>
namespace async
{
    int fib(int n)
    {
#ifdef __DELAY_
        std::this_thread::sleep_for(100ms);
#endif
        if (n < 2)
        {
            return n;
        }
        auto f = std::async(std::launch::async, [n]() {
            return fib(n - 1);
        });
        auto y = fib(n - 2);
        return y + f.get();
    }

    std::future<int> fib2(int n)
    {
        if (n<2)
        {
            co_return n;
        }
        auto fib0 = 0;
        auto fib1 = 1;
        for (size_t i = 2; i < n; i++)
        {
            //{fib0, fib1} = { fib1, (fib0 + fib1) };
            auto temp = co_await std::async(std::launch::async, [=]() {\
                return fib0 + fib1;
            });
            fib0 = fib1;
            fib1 = temp;
        }
        co_return (fib0 + fib1);
    }
}


#include <experimental/generator>
#include <spdlog/spdlog.h>
using std::experimental::generator;
generator<int> gen(int count)
{
    for (size_t i = 0; i < count; i++)
    {
        co_yield i;
    }
}