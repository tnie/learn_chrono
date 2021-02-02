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

template<>
struct Fib<0>
{
    constexpr static unsigned long value = 0;
};

template<>
struct Fib<1>
{
    constexpr static unsigned long value = 1;
};

//��������
template<int N>
unsigned long __fib(int i)
{
    constexpr int LIMIT = 45;
    if (i>= LIMIT) {
        throw std::runtime_error("undefined behavior.");
    }
    if (i == N) return Fib<N>::value;
    else {
        //�˴�����Ԫ����ʽ����������ʱ����ʵ������ɱ���ʧ��
        //return __fib<N + 1>(i); // ����ʵ�������� int ֵ
        //�������� i>=LIMIT �ͻ�����ʱ��ѭ��
        return __fib < N<LIMIT ? N + 1 : 0>(i);
    }
}

unsigned long fib2(int i)
{
    return __fib<0>(i);
}

int main()
{
    spdlog::info("start..");
    /*constexpr*/ int n = 40;
    //spdlog::info("Fib<{}>={}", n, Fib<n>::value);
    spdlog::info("Fib<{}>={}", n, fib2(n));
    spdlog::info("fib({})={}", n, fib(n));
    return 0;
}