#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <mutex>

#include "ThreadPool.h"

std::mutex mt;  // ���� count ͬ��

// https://blog.csdn.net/gcola007/article/details/78750220
// ��Ȼ�������Ǵ� https://github.com/progschj/ThreadPool ��ȫ�������ģ�ֻ�������� comment

int main()
{

    ThreadPool pool(4);
    std::vector< std::future<int> > results;

    for (int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue([] (int i){
            std::cout << "hello " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "world " << i << std::endl;
            return i*i;
        }, i)
        );
    }

    std::ostringstream oss;
    for (auto && result : results)    //ͨ��future.get()��ȡ����ֵ
    {
        oss << result.get() << ' ';
    }
    std::cout << oss.str() << std::endl;

    return 0;
}
