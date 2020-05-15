#pragma once
#include "add.h"
#include <experimental\coroutine>

// ��װ�첽�ӿڣ��û��ı��������ڿ⿪���ߵ�����֮��

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
