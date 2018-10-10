#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>

//If you run std::this_thread::sleep_for() and change the system clock, then the sleep time will be erroneous.
//The code below demonstrates this (rights of the administrator are needed) :

int main()
{
    std::thread th([]() {
        auto start = std::chrono::steady_clock::now();
        std::this_thread::sleep_for(std::chrono::seconds(10));
        //Sleep(10 * 1000);     // 绝对值十秒，对调整系统时间不敏感
        auto duration = std::chrono::steady_clock::now() - start;
        std::cout << std::chrono::duration_cast<std::chrono::seconds>(duration).count() << " seconds passed" << std::endl;
    });
    // 修改系统时间，需要“管理员权限”
    SYSTEMTIME st;
    FILETIME ft;
    GetSystemTime(&st);
    SystemTimeToFileTime(&st, &ft);
    unsigned long long tm = ((unsigned long long)ft.dwHighDateTime << 32) + ft.dwLowDateTime;
    tm -= 5 * 10000000;   // 输出：15 seconds passed
    //tm += 5 * 10000000;     // 输出：10 seconds passed，为什么不是 5 seconds passed 呢？
    ft.dwHighDateTime = tm >> 32;
    ft.dwLowDateTime = tm & 0xFFFFFFFF;
    FileTimeToSystemTime(&ft, &st);
    Sleep(100);
    SetSystemTime(&st);
    th.join();
    getchar();
    return 0;
}