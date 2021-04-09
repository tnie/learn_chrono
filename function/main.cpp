#include <spdlog\spdlog.h>
#include <functional>

using namespace std;

std::function<void(int)> echo;

void func(int i)
{
    spdlog::info("general function: {}", i);
}

struct Cal
{
    void operator()(int i)
    {
        spdlog::info("overload operator(): {}", i);
    }

    void foo(int i)
    {
        spdlog::info("member function: {}@{}", i, reinterpret_cast<uintptr_t>(this));
    }
};

namespace la
{
    void func(int i)
    {
        spdlog::info("general function: {}", i);
    }
}

int test()
{
    Cal in;
    in.foo(1);
    auto point = std::bind(&Cal::foo, &in, std::placeholders::_1);
    point(2);
    auto copy = std::bind(&Cal::foo, in, std::placeholders::_1);    // 拷贝传参，请务必明白在做什么
    copy(3);
    auto ref = std::bind(&Cal::foo, std::ref(in), std::placeholders::_1);
    ref(4);
    return 0;
}

int main()
{
    // 多余 const 时，报错位置不对，很难找
    using err_t = std::function<int(int) /*const*/>;
    err_t err = std::tolower;
    //return test();
    std::function<int(int)> func = std::tolower;
    std::function<int(int)> lamb = [](int a) { return a; };
    std::string str("niel");
    std::function<size_t(void)> bind = std::bind(&std::string::size, &str);
    std::function<int(int, int)> object = std::plus<int>();
    std::function<size_t(const std::string&)> p2mf = &std::string::size;
    spdlog::info(p2mf(str));

    //std::function<size_t(void)> bind = std::bind(&std::string::size, std::ref(str));
    //// 拷贝传参，请务必明白在做什么
    //std::function<size_t(void)> bind = std::bind(&std::string::size, str);

}
