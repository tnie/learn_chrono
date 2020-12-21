#include <Windows.h>
#include <thread>
#include <spdlog\spdlog.h>
#include <vector>

typedef struct
{
    HANDLE hFile;
} cp_key;                  //一个自定义数据 ，随便填吧

typedef struct
{
    OVERLAPPED overlap;
    char buf[1024];
} cp_overlapped;        //overlapped 放第一个, 相当于一个OVERLAPPED结构


unsigned int __stdcall io_thread(void *param)
{
    HANDLE iocp = (HANDLE)param;
    spdlog::info("线程创建完毕 iocp:{}", reinterpret_cast<uintptr_t>(iocp));
    DWORD bytesRead = 0;
    cp_key * key = 0;
    cp_overlapped * s = 0;
    DWORD ret = 0;

    while (1)
    {

        //等待完成端口的响应
        ret = GetQueuedCompletionStatus(iocp, &bytesRead, (LPDWORD)&key, (LPOVERLAPPED*)&s, INFINITE);

        //退出线程
        if (key == 0 && s == 0) {
            spdlog::info("exit");
            break;
        }
        spdlog::info("byteread:{}, key:{},ret :{}", bytesRead, reinterpret_cast<uintptr_t>(key->hFile), ret);
        spdlog::info("overlapped  offset:{}", s->overlap.Offset);
        spdlog::info("%s\n", s->buf);
    }
    return 0;
}

int main(int argc, char* argv[])
{
    //准备线程数量
    const int NThread = std::thread::hardware_concurrency() + 2;

    //创建一个完成端口
    HANDLE iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, NThread);
    std::vector<std::thread> thread_handles;
    thread_handles.reserve(NThread);

    //创建线程
    for (int i = 0; i < NThread; ++i)
        thread_handles.push_back(std::thread([iocp]() { io_thread(iocp); }));

    HANDLE hFile = CreateFile(
        TEXT("./test.cpp"),  //这里自己修改
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_OVERLAPPED,  //注意.
        NULL
    );
    DWORD numread = 0, ret = 0;

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
    ret = ReadFile(hFile, s->buf, 1024, &numread, &s->overlap);
    spdlog::info("readfile ret:{} , ERR:{}", ret, GetLastError());


    //等待一下
    for (int i = 0; i < 2; ++i)
        Sleep(1000);

    //告诉所有线程去死吧
    for (int i = 0; i < NThread; ++i)
        PostQueuedCompletionStatus(iocp, 0, (DWORD)0, 0);

    for (auto & th : thread_handles)
    {
        if (th.joinable())
        {
            th.join();
        }
    }

    return 0;
}