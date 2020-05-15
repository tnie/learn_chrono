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

#ifdef _ANOTHER__
    // 如果结果已经得到，不需要执行协程
    bool await_ready()
    {
        result_ = Add100Random(num_);
        return (result_!= nullptr);
    }
    // 返回类型为空的函数：执行完毕后直接让出执行
    void await_suspend(std::experimental::coroutine_handle<> h)
    {
        Add100ByCallback(num_,
            [h, this](int value)
        {
            result_ = std::make_shared<int>(value);
            h.resume();
        });
    }
#else
    bool await_ready()
    {
        return false;
    }
    // the awaiter might start an async operation that
    // can sometimes complete synchronously.
    bool await_suspend(std::experimental::coroutine_handle<> h)
    {
        if (result_ = Add100Random(num_))
            return false;
        Add100ByCallback(num_,
            [h, this](int value)
        {
            result_ = std::make_shared<int>(value);
            h.resume();
        });
        return true;
    }
#endif
    int await_resume()
    {
        if (result_)
        {
            return *result_;
        }
        throw std::exception("* nullptr");
    }
};
