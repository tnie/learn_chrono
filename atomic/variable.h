#pragma once
#include <thread>
#include <iostream>
#include <sstream>
#include <mutex>

void TestVariable()
{
    std::mutex mt;
    // ��volatile **����**��֤ȫ�����α����Ƕ��̰߳�ȫ��
    /*volatile*/ int global1 = 0;
    // ++/-- ������ͬʱ�漰��д

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
    // ������ʱ������ global1 ��������Ρ���ȫ��ԭ���������̶߳�д�ǲ���ȫ��
    std::cout << "ȫ��ԭ������: " << global1 << std::endl;

    auto fun3 = [] {
        static int static2;
        for (size_t i = 0; i < 100000; i++)
        {
            //lock_guard<mutex> lg(mt);
            ++static2;
            --static2;
        }
        std::ostringstream oss;
        // ������ʱ������ static2 ��������Ρ��ں�����̬�������̶߳�дҲ�ǲ���ȫ��
        oss << "������̬����: " << static2  << " at " << &static2 << std::endl;
        std::cout << oss.str();
    };
    std::thread t31(fun3);
    std::thread t32(fun3);
    t31.join();
    t32.join();
}
