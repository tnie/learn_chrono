#include <Windows.h>
#include <thread>
#include <spdlog\spdlog.h>
#include <tchar.h>
#include <locale>
#include <vector>

typedef struct
{
    HANDLE hFile;
} cp_key;                  //һ���Զ������� ��������

typedef struct
{
    OVERLAPPED overlap;
    char buf[1024];
} cp_overlapped;        //overlapped �ŵ�һ��, �൱��һ��OVERLAPPED�ṹ


unsigned int __stdcall io_thread(void *param)
{
    HANDLE iocp = (HANDLE)param;
    _tprintf(TEXT("�̴߳������ iocp:%p\n"), iocp);
    DWORD bytesRead = 0;
    cp_key * key = 0;
    cp_overlapped * s = 0;
    DWORD ret = 0;

    while (1)
    {

        //�ȴ���ɶ˿ڵ���Ӧ
        ret = GetQueuedCompletionStatus(iocp, &bytesRead, (LPDWORD)&key, (LPOVERLAPPED*)&s, INFINITE);

        //�˳��߳�
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

int main(int argc, char* argv[])
{
    _tsetlocale(LC_CTYPE, TEXT(""));
    //׼���߳�����
    const int NThread = std::thread::hardware_concurrency() + 2;

    //����һ����ɶ˿�
    HANDLE iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, NThread);
    std::vector<std::thread> thread_handles;
    thread_handles.reserve(NThread);

    //�����߳�
    for (int i = 0; i < NThread; ++i)
        thread_handles.push_back(std::thread([iocp]() { io_thread(iocp); }));

    HANDLE hFile = CreateFile(
        TEXT("./test.cpp"),  //�����Լ��޸�
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_OVERLAPPED,  //ע��.
        NULL
    );
    DWORD numread = 0, ret = 0;

    //��ʼ������ , ��Щ���ݽ�����ɺ󱻴��ݵ��߳���
    cp_overlapped * s = new cp_overlapped;
    s->overlap.hEvent = NULL;
    s->overlap.Offset = 0;
    s->overlap.OffsetHigh = 0;

    //��ʼ������ , ��Щ���ݽ�����ɺ󱻴��ݵ��߳���
    cp_key * key = new cp_key;
    key->hFile = hFile;

    //���ļ�handle �� ��ɶ˿� ������һ�� , ע�� key ������ת��
    CreateIoCompletionPort(hFile, iocp, (DWORD)key, 0);

    //��ȡ�ļ� , �ȶ����, ����һ���̴߳�������Ĳ���
    //ע�� cp_overlapped ��ʹ��, �ڶ����, ����һ���߳̽���ȡ������
    ret = ReadFile(hFile, s->buf, 1024, &numread, &s->overlap);
    printf("readfile ret:%d , ERR:%d\n", ret, GetLastError());


    //�ȴ�һ��
    for (int i = 0; i < 2; ++i)
        Sleep(1000);

    //���������߳�ȥ����
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