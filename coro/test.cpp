#include <iostream>
#include <thread>
#include <experimental\coroutine>
#include <spdlog\spdlog.h>
#include "task.h"
#include "addawaiter.h"
using namespace std;

// �û��ĸ���
Task Add100Coroutine(int a)
{
    int ret = co_await Add100Awaiter(a);
    spdlog::info("A get result from coroutine: {}", ret);
    ret = co_await Add100Awaiter(a);
    spdlog::info( "B get result from coroutine: {}" ,ret );
    Add100Coroutine(10);
    co_return;
}

//�ο� https://devblogs.microsoft.com/oldnewthing/20191209-00/?p=103195
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

// Э�̵ķ���ֵ�����ں�Э�̽���������ָ�ִ�У�
// Ϊ�˼򵥣�Э�̵ķ���ֵֻʵ��Ҫ��Ľӿڣ���ʲô���ܶ��������� Task ����
Task simplest_coro()
{
    // �������Э�����лָ������Ǹ�����û����ͣ
    co_await experimental::suspend_never();
    // �����ͣ���޷��ָ�
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
    getchar();  // ��ª�ġ���εȴ�������������
    return 0;
}
