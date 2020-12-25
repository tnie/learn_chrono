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
    co_return;
}

int main()
{
    for (size_t i = 0; i < 5; i++)
    {
        Add100Coroutine(i);
    }
    getchar();  // ��ª�ġ���εȴ�������������
    return 0;
}
