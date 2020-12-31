#pragma once
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

void TestFlag()
{
    //std::atomic_flag 是原子布尔类型。不同于所有 std::atomic 的特化，它保证是免锁的。
    // 和 typedef atomic<bool> atomic_bool; 不同的
    std::atomic_flag lock_cout = ATOMIC_FLAG_INIT;

    std::vector<std::thread> ts;
    for (size_t i = 0; i < 10; i++)
    {
        ts.push_back(std::thread([&, x=i] {
            for (size_t i = 0; i < 10; i++)
            {
                // 自旋锁。不使用自旋锁或互斥锁，打印存在竞争，输出混乱
                while (lock_cout.test_and_set())
                    ;   // spin
                std::cout << "Output form " << "threadd #" << x << "\n";
                lock_cout.clear();
            }
        }));
    }

    for (auto & var : ts)
    {
        var.join();
    }
}

