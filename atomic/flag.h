#pragma once
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

void TestFlag()
{
    //std::atomic_flag ��ԭ�Ӳ������͡���ͬ������ std::atomic ���ػ�������֤�������ġ�
    // �� typedef atomic<bool> atomic_bool; ��ͬ��
    std::atomic_flag lock_cout = ATOMIC_FLAG_INIT;

    std::vector<std::thread> ts;
    for (size_t i = 0; i < 10; i++)
    {
        ts.push_back(std::thread([&, x=i] {
            for (size_t i = 0; i < 10; i++)
            {
                // ����������ʹ���������򻥳�������ӡ���ھ������������
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

