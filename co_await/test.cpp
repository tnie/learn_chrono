#include "ffib.h"
#include <chrono>

#define _NOW_MILLI \
    std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();


int main()
{
    //auto fib = async::fib;
    auto fib = async::fib2;
    for (size_t i = 0; i < 10; i++)
    {
        spdlog::info("{}: {}", i, fib(i).get());
    }
    auto t1 = _NOW_MILLI;
    const auto i = 15;
    spdlog::info("{}: {}", i, fib(i).get());
    auto t2 = _NOW_MILLI;
    spdlog::warn("fib({}) cost {}ms",i,  t2 - t1);
    return 0;
}