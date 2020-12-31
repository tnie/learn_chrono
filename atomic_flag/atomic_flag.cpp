#include <iostream>
#include <mutex>
#include <atomic>
#include <vector>
#include <thread>
#include <sstream>

using namespace std;

//std::atomic_flag ��ԭ�Ӳ������͡���ͬ������ std::atomic ���ػ�������֤�������ġ�
// �� typedef atomic<bool> atomic_bool; ��ͬ��
atomic_flag lock_cout = ATOMIC_FLAG_INIT;

void append_number(int x)
{
    for (size_t i = 0; i < 10; i++)
    {
        // ����������ʹ���������򻥳�������ӡ���ھ������������
        while (lock_cout.test_and_set())
            ;   // spin
        cout << "Output form " << "threadd #" << x << "\n";
        lock_cout.clear();
    }

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