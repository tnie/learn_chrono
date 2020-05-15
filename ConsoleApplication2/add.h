#pragma once
#include <functional>
#include <thread>
#include <spdlog/spdlog.h>

// 模拟常规的耗时任务
int Add100(int a)
{
    spdlog::info("calculating...");
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return a + 100;
}

// 模拟异步 IO 形式的异步调用
void Add100ByCallback(int a, std::function<void(int)> fun)
{
    std::thread([a, fun]() {
        int ret = Add100(a);
        fun(ret);
    })
        .detach();  // TODO 转移到全局的线程池来做
}

