#include "ffib.h"
#include <fmt\chrono.h>
#include <spdlog\spdlog.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
    auto fib = async_fib;
    auto t1 = chrono::system_clock::now();
    const auto i = 15;
    auto value = fib(i).get();
    auto t2 = chrono::system_clock::now();
    spdlog::warn("fib({})={} cost {}ms", i, value,
        chrono::duration_cast<milliseconds>(t2 - t1).count());
    return 0;
}