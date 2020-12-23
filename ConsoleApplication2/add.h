#pragma once
#include <functional>
#include <thread>
#include <spdlog/spdlog.h>
#include <memory>
#include <random>

// ģ�ⳣ��ĺ�ʱ����
int Add100(int a)
{
    spdlog::info("calculating...");
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return a + 100;
}

// ģ���첽 IO ��ʽ���첽����
void Add100ByCallback(int a, std::function<void(int)> fun)
{
    std::thread([a, fun]() {
        int ret = Add100(a);
        fun(ret);
    })
        .detach();  // TODO ת�Ƶ�ȫ�ֵ��̳߳�����
}

int random()
{
    if (false)
    {
        // NOTE ���Ӳ��䣬������в���
        std::srand(std::time(nullptr)); // �Ե�ǰʱ��Ϊ���������������
        return std::rand();
    }
    else
    {
        // �����ֵ���֣�������
        std::random_device r;
        // ѡ�� 1 �� 6 ��������
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(1, 6);
        return uniform_dist(e1);
    }
}

// �ܹ��������ɽ����������ʧ��
std::shared_ptr<int> Add100Random(int a)
{
    int random_variable = random();
    if (random_variable % 2 == 0)
    {
        return std::make_shared<int>(a + 100);
    }
    return nullptr;
}

