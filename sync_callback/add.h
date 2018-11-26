#pragma once
#include <chrono>
#include <thread>
#include <functional>
#include <string>

// 二十以内加减法
int add(int a, int b)
{
    if (a < 0 || b < 0)
    {
        throw std::exception("加数或被加数不能为负");
    }
    if (a >20 || b > 20)
    {
        throw std::exception("加数或被加数不能大于二十");
    }
    return a + b;
}

using FunT = std::function<void(std::string err, int sum)>;
void add_callback(int a, int b, const FunT & cb)
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
    if (a < 0 || b < 0)
    {
        cb("加数或被加数不能为负", 0);
    }
    else if (a > 20 || b > 20)
    {
        cb("加数或被加数不能大于二十", 0);
    }
    else
    {
        cb("", a + b);
    }
}

// TODO
int async_add(int a, int b, const FunT & cb);