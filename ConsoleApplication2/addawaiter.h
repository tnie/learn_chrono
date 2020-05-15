#pragma once
#include "add.h"
#include <experimental\coroutine>

// 封装异步接口：用户的便利建立在库开发者的辛苦之上

struct Add100Awaiter
{
    int num_;
    std::shared_ptr<int> result_;
    Add100Awaiter(int a) :num_(a)
    {

    }
    // 如果结果已经得到，不需要执行协程
    bool await_ready()
    {
        result_ = Add100Random(num_);
        return (result_!= nullptr);
    }
    void await_suspend(std::experimental::coroutine_handle<> h)
    {
        Add100ByCallback(num_,
            [h, this](int value)
        {
            result_ = std::make_shared<int>(value);
            h.resume();
        });
    }
    int await_resume()
    {
        if (result_)
        {
            return *result_;
        }
        throw std::exception("* nullptr");
    }
};
