#include <Windows.h>
#include <thread>
#include <spdlog\spdlog.h>
#include <vector>
#include "utility.h"

// TODO 内存泄漏、
// TODO 多线程意义，只读一个文件创建多个线程，为了演示而演示

// 程序用途：遍历当前仓库中的 .h/cpp 文件，并输出其中的空白字符数量
// TODO 1.怎么结束（执行完毕或强制退出） 2.错误处理
// 学习步骤：读写文件，线程使用，网络编程，完成端口

typedef struct
{
    HANDLE hFile;
    int offset{0};  // 已读内容 TODO 多线程竞争吗
} cp_key;                  //一个自定义数据 ，随便填吧

typedef struct
{
    OVERLAPPED overlap;
    char buf[1024];     // TODO 是常规操作还是诡计，CONTAINING_RECORD 宏
} cp_overlapped;        //overlapped 放第一个, 相当于一个OVERLAPPED结构


unsigned int __stdcall io_thread(void *param)
{
    HANDLE iocp = (HANDLE)param;
    spdlog::info("线程创建完毕 iocp:{}", reinterpret_cast<uintptr_t>(iocp));
    DWORD bytesRead = 0;
    cp_key * key = 0;
    cp_overlapped * s = 0;

    while (1)
    {

        //等待完成端口的响应
        BOOL ret = GetQueuedCompletionStatus(iocp, &bytesRead, (LPDWORD)&key, (LPOVERLAPPED*)&s, INFINITE);

        //退出线程
        if (key == 0 && s == 0) {
            spdlog::info("exit");
            return 0;
        }
        spdlog::info("byteread:{}, key:{},ret :{}", bytesRead, reinterpret_cast<uintptr_t>(key->hFile), ret);
        //printf("%.*s\n",bytesRead, s->buf);
        spdlog::info("{:.{}}", s->buf, bytesRead);  //a non-null terminated string
        if (ret)
        {
            key->offset += bytesRead;
            if (bytesRead < sizeof(s->buf))
            {
                //delete s;
                //delete key;
                spdlog::info("finish");
                //return 0;   // 要分担任务的
            }
            else
            {
                memset(s, 0, sizeof(cp_overlapped));
                s->overlap.Offset = key->offset;
                BOOL ret = ReadFile(key->hFile, s->buf, sizeof(s->buf), NULL, &s->overlap);
                spdlog::info("ReadFile 返回值:{} , ERR:{}", ret, GetLastError());
            }
        }
        else
        {
            spdlog::error("key:{},ret :{}, ERR:{} ", reinterpret_cast<uintptr_t>(key->hFile), ret, GetLastError());
            return EXIT_FAILURE;
        }
    }
    return 0;
}

inline std::wstring s2ws(const std::string& str)
{
    return std::wstring{ str.begin(), str.end() };
}

void ReadFile(HANDLE & iocp, const std::string& file)
{
    HANDLE hFile = CreateFile(
        s2ws(file).c_str(),  //这里自己修改
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_OVERLAPPED,  //注意.
        NULL
    );

    //初始化数据 , 这些数据将在完成后被传递到线程中
    cp_overlapped * s = new cp_overlapped;
    s->overlap.hEvent = NULL;
    s->overlap.Offset = 0;
    s->overlap.OffsetHigh = 0;

    //初始化数据 , 这些数据将在完成后被传递到线程中
    cp_key * key = new cp_key;
    key->hFile = hFile;

    //将文件handle 与 完成端口 关联在一起 , 注意 key 的类型转换
    CreateIoCompletionPort(hFile, iocp, (DWORD)key, 0);

    //读取文件 , 等读完后, 将有一个线程处理读完后的步骤
    //注意 cp_overlapped 的使用, 在读完后, 其中一个线程将获取此数据
    BOOL ret = ReadFile(hFile, s->buf, sizeof(s->buf), NULL, &s->overlap);
    spdlog::info("ReadFile 返回值:{} , ERR:{}", ret, GetLastError());
    if (ret)
    {
        //文件真是被读完了，rc为true
        // 或当数据被放入cache中，或操作系统认为它可以很快速地取得数据，rc为true
    }
    else
    {
        if (GetLastError() == ERROR_IO_PENDING)
        {
            //当错误是ERROR_IO_PENDING,那意味着读文件的操作还在进行中
            //等候，直到文件读完
            //WaitForSingleObject(hFile, INFINITE);
            //rc = GetOverlappedResult(hFile, &overlap, &numread, FALSE);
            //上面二条语句完成的功能与下面一条语句的功能等价：
            // GetOverlappedResult(hFile,&overlap,&numread,TRUE);
        }
        else
        {
            //出错了
        }
    }
}

int main(int argc, char* argv[])
{
    // 打印线程号
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%^%l%$] %v");
    vector<string> files;
    cf_findFileFromDir(R"(F:\_DayK)", files);
    //准备线程数量
#ifdef _DEBUG
    const int NThread = 2;
#else
    const int NThread = std::thread::hardware_concurrency() + 2;
#endif // _DEBUG

    //创建一个完成端口
    HANDLE iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, NThread);
    std::vector<std::thread> thread_handles;
    thread_handles.reserve(NThread);

    //创建线程
    for (int i = 0; i < NThread; ++i)
        thread_handles.push_back(std::thread([iocp]() { io_thread(iocp); }));

    for (auto& file : files)
    {
        //if (file.rfind(".cpp") != string::npos)   // TODO 读全部会报错
        {
            ReadFile(iocp, file);
        }
    }

    //告诉所有线程去死吧
    for (int i = 0; i < NThread; ++i)
        //PostQueuedCompletionStatus(iocp, 0, (DWORD)0, 0);

    for (auto & th : thread_handles)
    {
        if (th.joinable())
        {
            th.join();
        }
    }

    return EXIT_SUCCESS;
}