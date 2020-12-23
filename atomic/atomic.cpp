#include <thread>
#include <mutex>
#include <vector>
#include <atomic>
#include <iostream>
#include <chrono>

using namespace std;
// 全局的结果数据
atomic_long total = 0;
mutex mt;

// 点击函数
void click()
{
    for (int i = 0; i < 1000000; ++i)
    {
        // 对全局数据进行无锁访问
        //lock_guard<mutex> lg(mt);
        total += 1;
    }
}


int main()
{
    // 计时开始
    auto start = chrono::steady_clock::now();
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
    cout << "result:" << total << endl;
    cout << "duration:" << (chrono::duration_cast<chrono::milliseconds>(finish - start)).count() << "ms" << endl;
    return 0;
}