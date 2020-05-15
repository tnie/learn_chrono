#pragma once
#include "add.h"
#include <experimental\coroutine>

// ��װ�첽�ӿڣ��û��ı��������ڿ⿪���ߵ�����֮��

struct Add100Awaiter
{
    int num_;
    std::shared_ptr<int> result_;
    Add100Awaiter(int a) :num_(a)
    {

    }

#ifdef _ANOTHER__
    // �������Ѿ��õ�������Ҫִ��Э��
    bool await_ready()
    {
        result_ = Add100Random(num_);
        return (result_!= nullptr);
    }
    // ��������Ϊ�յĺ�����ִ����Ϻ�ֱ���ó�ִ��
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
