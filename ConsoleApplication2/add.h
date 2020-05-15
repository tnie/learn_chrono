#pragma once
#include <functional>
#include <thread>
#include <spdlog/spdlog.h>
#include <memory>
#include <random>

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

int random()
{
    if (false)
    {
        // NOTE 种子不变，随机序列不变
        std::srand(std::time(nullptr)); // 以当前时间为随机生成器的种子
        return std::rand();
    }
    else
    {
        // 以随机值播种，若可能
        std::random_device r;
        // 选择 1 与 6 间的随机数
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(1, 6);
        return uniform_dist(e1);
    }
}

// 能够快速生成结果，但可能失败
std::shared_ptr<int> Add100Random(int a)
{
    int random_variable = random();
    if (random_variable % 2 == 0)
    {
        return std::make_shared<int>(a + 100);
    }
    return nullptr;
}

