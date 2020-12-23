#include <thread>
#include <mutex>
#include <vector>
#include <atomic>
#include <iostream>
#include <chrono>

using namespace std;
// ȫ�ֵĽ������
atomic_long total = 0;
mutex mt;

// �������
void click()
{
    for (int i = 0; i < 1000000; ++i)
    {
        // ��ȫ�����ݽ�����������
        //lock_guard<mutex> lg(mt);
        total += 1;
    }
}


int main()
{
    // ��ʱ��ʼ
    auto start = chrono::steady_clock::now();
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
    cout << "result:" << total << endl;
    cout << "duration:" << (chrono::duration_cast<chrono::milliseconds>(finish - start)).count() << "ms" << endl;
    return 0;
}