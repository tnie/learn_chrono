//#include <vld.h>
#include <exception>
#include <spdlog\spdlog.h>
#include <thread>
#include <future>

//跨线程捕获异常

int f()
{
    throw std::runtime_error("runtime error");
}

int main()
{
    try
    {
        if (false)
        {
            //if the function f returns a value or throws an exception, it is stored in
            //the shared state accessible through the std::future that async returns to the caller.
            std::future<int> future_c = std::async(std::launch::async, f);
            //If an exception was stored in the shared state referenced by the future
            //then that exception will be thrown.
            int c = future_c.get();
            spdlog::info(c);
        }
        if (false)
        {
            //不能跨线程捕获异常
            std::thread th(f);
            th.join();
        }
        if (true)
        {
            std::exception_ptr eptr;
            std::thread th([&eptr]() {
                try
                {
                    f();
                }
                catch (.../*const std::exception&*/)
                {
                    eptr = std::current_exception();
                }
            });
            th.join();
            if (eptr)
            {
                std::rethrow_exception(eptr);
            }
        }
    }
    catch (const std::exception& e)
    {
        spdlog::warn(e.what());
    }
    return 0;
}