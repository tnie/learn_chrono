#pragma once
#include <functional>
#include <thread>
#include <spdlog/spdlog.h>

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

