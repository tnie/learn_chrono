#pragma once
#include <thread>
#include <iostream>
#include <sstream>
#include <mutex>

void TestVariable()
{
    std::mutex mt;
    // ③volatile **不能**保证全局整形变量是多线程安全的
    /*volatile*/ int global1 = 0;
    // ++/-- 操作符同时涉及读写

    std::thread t1([&] {
        for (size_t i = 0; i < 100000; i++)
        {
            //lock_guard<mutex> lg(mt);
            ++global1;
        }
    });
    std::thread t2([&] {
        for (size_t i = 0; i < 100000; i++)
        {
            //lock_guard<mutex> lg(mt);
            --global1;
        }
    });
    t1.join();
    t2.join();
    // 不加锁时，出现 global1 非零的情形。①全局原生变量多线程读写是不安全的
    std::cout << "全局原生变量: " << global1 << std::endl;

    auto fun3 = [] {
        static int static2;
        for (size_t i = 0; i < 100000; i++)
        {
            //lock_guard<mutex> lg(mt);
            ++static2;
            --static2;
        }
        std::ostringstream oss;
        // 不加锁时，出现 static2 非零的情形。②函数静态变量多线程读写也是不安全的
        oss << "函数静态变量: " << static2  << " at " << &static2 << std::endl;
        std::cout << oss.str();
    };
    std::thread t31(fun3);
    std::thread t32(fun3);
    t31.join();
    t32.join();
}
