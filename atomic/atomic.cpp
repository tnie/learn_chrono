#include <thread>
#include <mutex>
#include <vector>
#include <atomic>
#include <iostream>
#include <chrono>
#include <spdlog\spdlog.h>
#include <fmt\chrono.h>

using namespace std;
// 全局的结果数据
//typedef atomic<long> atomic_long; // 类型别名
atomic_long atomicTotal{ 0 };
long total = 0;
mutex mt;

// 点击函数
void click()
{
    for (int i = 0; i < 10000; ++i)
    {
        atomicTotal += 1;
        // 对全局数据进行无锁访问
        //lock_guard<mutex> lg(mt);
        total += 1;
    }
}

void test()
{
    struct notTri
    {
        std::string name;
    };
    spdlog::info("std::atomic<long>::is_lock_free() {}", atomicTotal.is_lock_free());
    //C2338 atomic<T> requires T to be trivially copyable.
    //spdlog::info("std::atomic<Tri>().is_lock_free() {}", std::atomic<notTri>().is_lock_free());
    struct Demo
    {
        char name[10];
    };
    // 原子类型可用互斥或其他锁定操作实现，而不一定用免锁的原子 CPU 指令。
    spdlog::info("std::atomic<Demo>().is_lock_free() {}", std::atomic<Demo>().is_lock_free());  // false
}

void TestValue()
{
    // 计时开始
    auto start = chrono::steady_clock::now();
    spdlog::info("start...");
    // 创建100个线程模拟点击统计
    vector<thread> threads;
    for (int i = 0; i < 100; ++i)
    {
        threads.push_back(thread(click));
    }

    for (auto & var : threads)
    {
        var.join();
    }
    // 计时结束
    auto finish = chrono::steady_clock::now();
    // 输出结果
    spdlog::info("total is {} vs. {}, duration is {}.", total, atomicTotal,
        chrono::duration_cast<chrono::milliseconds>(finish - start));
}


//std::atomic_flag 是原子布尔类型。不同于所有 std::atomic 的特化，它保证是免锁的。
// 和 typedef atomic<bool> atomic_bool; 不同的
atomic_flag lock_cout = ATOMIC_FLAG_INIT;

void append_number(int x)
{
    for (size_t i = 0; i < 10; i++)
    {
        // 自旋锁。不使用自旋锁或互斥锁，打印存在竞争，输出混乱
        while (lock_cout.test_and_set())
            ;   // spin
        cout << "Output form " << "threadd #" << x << "\n";
        lock_cout.clear();
    }

}

void TestFlag()
{
    vector<thread> ts;
    for (size_t i = 0; i < 10; i++)
    {
        ts.push_back(thread(append_number, i));
    }

    for (auto & var : ts)
    {
        var.join();
    }
}

int main()
{
    TestValue();
    test();
    TestFlag();
    return 0;
}