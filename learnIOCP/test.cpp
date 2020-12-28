#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include <tchar.h>
#include <locale>

// Դ�뿽���ԣ��Լ�����ͷ�ļ�
// https://blog.csdn.net/dashoumeixi/article/details/83587590

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

int _tmain(int argc, _TCHAR* argv[])
{
    _tsetlocale(LC_CTYPE, TEXT(""));
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    //׼���߳�����
    const int NThread = sysInfo.dwNumberOfProcessors + 2;

    //����һ����ɶ˿�
    HANDLE iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, NThread);
    HANDLE * thread_handles = new HANDLE[NThread];

    //�����߳�
    for (int i = 0; i < NThread; ++i)
        thread_handles[i] = (HANDLE)_beginthreadex(0, 0, io_thread, (void*)iocp, 0, 0);

    HANDLE hFile = CreateFile(
        TEXT("D:/download/bookmarks.html"),  //�����Լ��޸�
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

    WaitForMultipleObjects(NThread, thread_handles, TRUE, -1);

    return 0;
}