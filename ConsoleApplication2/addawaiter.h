#pragma once
#include "add.h"
#include <experimental\coroutine>

// ��װ�첽�ӿڣ��û��ı��������ڿ⿪���ߵ�����֮��
//https://lewissbaker.github.io/2017/11/17/understanding-operator-co-await
struct Add100Awaiter
{
    int num_;
    std::shared_ptr<int> result_;
    Add100Awaiter(int a) :num_(a)
    {

    }

#ifndef _ANOTHER__
    // �������Ѿ��õ�������Ҫִ��Э��
    //The purpose of the await_ready() method is to
    //allow you to avoid the cost of the <suspend-coroutine> operation
    bool await_ready()
    {
        result_ = Add100Random(num_);
        return (result_!= nullptr);
    }
    // ��������Ϊ�յĺ�����ִ����Ϻ�ֱ���ó�ִ��
    // �����һ���ɱ��������ɵı���
    void await_suspend(std::experimental::coroutine_handle<> h)
    {
        auto call = [h, this](int value)
        {
            result_ = std::make_shared<int>(value);
            h.resume();
            spdlog::debug("");
        };
        Add100ByCallback(num_, call);
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
        auto call = [h, this](int value)
        {
            result_ = std::make_shared<int>(value);
            //It is the responsibility of the await_suspend() method to
            //schedule the coroutine for resumption(or destruction) at
            //some point in the future once the operation has completed.
            h.resume();
        };
        Add100ByCallback(num_, call);
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
