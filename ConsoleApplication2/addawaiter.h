#pragma once
#include "add.h"
#include <experimental\coroutine>

// 封装异步接口：用户的便利建立在库开发者的辛苦之上

struct Add100Awaiter
{
    int num_;
    int result_;
    Add100Awaiter(int a) :num_(a)
    {

    }
    bool await_ready()
    {
        return false;
    }
    void await_suspend(std::experimental::coroutine_handle<> h)
    {
        Add100ByCallback(num_,
            [h, this](int value)
        {
            result_ = value;
            h.resume();
        });
    }
    bool await_resume()
    {
        return result_;
    }
};
