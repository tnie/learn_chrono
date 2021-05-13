#include <iostream>
#include <thread>
#include <experimental\coroutine>
#include <spdlog\spdlog.h>
#include "task.h"
#include "addawaiter.h"
using namespace std;

// 用户的福利
Task Add100Coroutine(int a)
{
    int ret = co_await Add100Awaiter(a);
    spdlog::info("A get result from coroutine: {}", ret);
    ret = co_await Add100Awaiter(a);
    spdlog::info( "B get result from coroutine: {}" ,ret );
    Add100Coroutine(10);
    co_return;
}

//参考 https://devblogs.microsoft.com/oldnewthing/20191209-00/?p=103195
struct awaiter : public experimental::suspend_always
{
    const std::string important = "Therefore, it is important that your awaiter not use its this pointer \
once it has arranged for the handle to be invoked somehow, \
because the this pointer may no longer be valid.";
    ~awaiter()
    {
        spdlog::warn("awaiter destructor.");
    }
    void await_suspend(experimental::coroutine_handle<> handle)
    {
        spdlog::info("the handle to be invoked ");
        handle.resume();
        spdlog::info("before the await_suspend finishes running.");
        if (false)
        {
            //Therefore, it is important that your awaiter not use its this pointer
            //once it has arranged for the handle to be invoked somehow,
            //because the this pointer may no longer be valid.
            spdlog::error(this->important);
        }
    }
};

struct resume_new_thread : std::experimental::suspend_always
{
    void await_suspend(
        std::experimental::coroutine_handle<> handle)
    {
        std::thread([handle] { handle.resume(); }).detach();
    }
};

// 协程的返回值，用于和协程交互（比如恢复执行）
// 为了简单，协程的返回值只实现要求的接口，但什么功能都不做。见 Task 定义
Task simplest_coro()
{
    // 这个不是协程自行恢复，而是根本就没有暂停
    co_await experimental::suspend_never();
    // 这个暂停了无法恢复
    //co_await experimental::suspend_always();

    co_await awaiter();
    spdlog::info("The entire function have run to completion!");

    co_await resume_new_thread();
    spdlog::info("Pay attention to thread id. your coroutine resumes in a new thread. ");
}

int main()
{
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%^%l%$] %v");
    simplest_coro();
    return 0;
    for (size_t i = 0; i < 1; i++)
    {
        Add100Coroutine(i);
    }
    getchar();  // 丑陋的。如何等待任务或放弃任务？
    return 0;
}
