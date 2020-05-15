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
    spdlog::info("get result from coroutine: {}", ret);
    ret = co_await Add100Awaiter(a);
    spdlog::info( "get result from coroutine: {}" ,ret );
}

int main()
{
    Add100Coroutine(100);
    Add100Coroutine(100);
    getchar();  // 丑陋的。如何等待任务或放弃任务？
    return 0;
}
