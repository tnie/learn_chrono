#include "spdlog\spdlog.h"

//https://www.jianshu.com/p/cb03a35ce879

unsigned long fib(int n)
{
    if (n < 2) return n;
    else return fib(n - 1) + fib(n - 2);
}

template<unsigned long N>
struct Fib
{
    constexpr static unsigned long value =
        Fib<N - 1>::value + Fib<N - 2>::value;
};

//特化终结递归，否则上面那个递归会死循环，编译时报错
template<> struct Fib<0> { constexpr static unsigned long value = 0; };
template<> struct Fib<1> { constexpr static unsigned long value = 1; };


//辅助函数
template<int N, int LIMIT = 45>
unsigned long __fib(int i)
{
    if (i>= LIMIT) {
        throw std::runtime_error("undefined behavior.");
    }
    if (i == N) return Fib<N>::value;
    else {
        //此处的三元表达式避免了运行时无限实例化造成编译失败
        //return __fib<N + 1>(i); // 无限实例化所有 int 值
        //但如果入参 i>=LIMIT 就会运行时死循环
        return __fib < N<LIMIT ? N + 1 : 0>(i);
    }
}

unsigned long fib2(int i)
{
    //it's correct, but is deprecated.
    //return __fib<30>(i);  // -> __fib<0>(i)
    return __fib<0>(i);
}

int main()
{
    spdlog::info("start..");
    /*constexpr*/ int n = 5;
    //spdlog::info("Fib<{}>={}", n, Fib<n>::value);
    spdlog::info("Fib<{}>={}", n, fib2(n));
    spdlog::info("fib({})={}", n, fib(n));
    return 0;
}