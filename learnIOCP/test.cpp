#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include <tchar.h>
#include <locale>

// 源码拷贝自，自己补充头文件
// https://blog.csdn.net/dashoumeixi/article/details/83587590

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
    _tprintf(TEXT("线程创建完毕 iocp:%p\n"), iocp);
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
            _tprintf(TEXT("exit"));
            break;
        }
        _tprintf(TEXT("byteread:%d, key:%p,ret :%d\n"), bytesRead, key->hFile, ret);
        _tprintf(TEXT("overlapped  offset:%d\n"), s->overlap.Offset);
        _tprintf(TEXT("%s\n"), s->buf);
    }
    return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
    _tsetlocale(LC_CTYPE, TEXT(""));
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    //准备线程数量
    const int NThread = sysInfo.dwNumberOfProcessors + 2;

    //创建一个完成端口
    HANDLE iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, NThread);
    HANDLE * thread_handles = new HANDLE[NThread];

    //创建线程
    for (int i = 0; i < NThread; ++i)
        thread_handles[i] = (HANDLE)_beginthreadex(0, 0, io_thread, (void*)iocp, 0, 0);

    HANDLE hFile = CreateFile(
        TEXT("D:/download/bookmarks.html"),  //这里自己修改
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
    printf("readfile ret:%d , ERR:%d\n", ret, GetLastError());


    //等待一下
    for (int i = 0; i < 2; ++i)
        Sleep(1000);

    //告诉所有线程去死吧
    for (int i = 0; i < NThread; ++i)
        PostQueuedCompletionStatus(iocp, 0, (DWORD)0, 0);

    WaitForMultipleObjects(NThread, thread_handles, TRUE, -1);

    return 0;
}