#include <iostream>
#include <mutex>
#include <atomic>
#include <vector>
#include <thread>
#include <sstream>

using namespace std;

mutex mt;
atomic_flag lock_cout = ATOMIC_FLAG_INIT;

void append_number(int x)
{
    // ��ʽ��
    //lock_guard<mutex> lg(mt);
    // ��ʽ�ڣ�������
    while (lock_cout.test_and_set())
    {
        // �� sleep ����ѭ���ǳ���
        this_thread::sleep_for(1ms);
    }
    cout << "threadd #" << x << endl;
    lock_cout.clear();
}

int main()
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
    return 0;
}