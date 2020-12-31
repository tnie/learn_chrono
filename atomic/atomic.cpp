#include <thread>
#include <mutex>
#include <vector>
#include <atomic>
#include <iostream>
#include <chrono>
#include <spdlog\spdlog.h>
#include <fmt\chrono.h>

using namespace std;
// ȫ�ֵĽ������
//typedef atomic<long> atomic_long; // ���ͱ���
atomic_long atomicTotal{ 0 };
long total = 0;
mutex mt;

// �������
void click()
{
    for (int i = 0; i < 10000; ++i)
    {
        atomicTotal += 1;
        // ��ȫ�����ݽ�����������
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
    // ԭ�����Ϳ��û����������������ʵ�֣�����һ����������ԭ�� CPU ָ�
    spdlog::info("std::atomic<Demo>().is_lock_free() {}", std::atomic<Demo>().is_lock_free());  // false
}

int main()
{
    // ��ʱ��ʼ
    auto start = chrono::steady_clock::now();
    spdlog::info("start...");
    // ����100���߳�ģ����ͳ��
    vector<thread> threads;
    for (int i = 0; i < 100; ++i)
    {
        threads.push_back(thread(click));
    }

    for (auto & var : threads)
    {
        var.join();
    }
    // ��ʱ����
    auto finish = chrono::steady_clock::now();
    // ������
    spdlog::info("total is {} vs. {}, duration is {}.", total, atomicTotal,
        chrono::duration_cast<chrono::milliseconds>(finish - start));

    test();
    return 0;
}