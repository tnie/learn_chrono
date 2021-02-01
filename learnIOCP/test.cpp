#include <Windows.h>
#include <thread>
#include <spdlog\spdlog.h>
#include <vector>
#include "utility.h"

// TODO �ڴ�й©��
// TODO ���߳����壬ֻ��һ���ļ���������̣߳�Ϊ����ʾ����ʾ

// ������;��������ǰ�ֿ��е� .h/cpp �ļ�����������еĿհ��ַ�����
// TODO 1.��ô������ִ����ϻ�ǿ���˳��� 2.������
// ѧϰ���裺��д�ļ����߳�ʹ�ã������̣���ɶ˿�

typedef struct
{
    HANDLE hFile;
    int offset{0};  // �Ѷ����� TODO ���߳̾�����
} cp_key;                  //һ���Զ������� ��������

typedef struct
{
    OVERLAPPED overlap;
    char buf[1024];     // TODO �ǳ���������ǹ�ƣ�CONTAINING_RECORD ��
} cp_overlapped;        //overlapped �ŵ�һ��, �൱��һ��OVERLAPPED�ṹ


unsigned int __stdcall io_thread(void *param)
{
    HANDLE iocp = (HANDLE)param;
    spdlog::info("�̴߳������ iocp:{}", reinterpret_cast<uintptr_t>(iocp));
    DWORD bytesRead = 0;
    cp_key * key = 0;
    cp_overlapped * s = 0;

    while (1)
    {

        //�ȴ���ɶ˿ڵ���Ӧ
        BOOL ret = GetQueuedCompletionStatus(iocp, &bytesRead, (LPDWORD)&key, (LPOVERLAPPED*)&s, INFINITE);

        //�˳��߳�
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
                //return 0;   // Ҫ�ֵ������
            }
            else
            {
                memset(s, 0, sizeof(cp_overlapped));
                s->overlap.Offset = key->offset;
                BOOL ret = ReadFile(key->hFile, s->buf, sizeof(s->buf), NULL, &s->overlap);
                spdlog::info("ReadFile ����ֵ:{} , ERR:{}", ret, GetLastError());
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
        s2ws(file).c_str(),  //�����Լ��޸�
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_OVERLAPPED,  //ע��.
        NULL
    );

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
    BOOL ret = ReadFile(hFile, s->buf, sizeof(s->buf), NULL, &s->overlap);
    spdlog::info("ReadFile ����ֵ:{} , ERR:{}", ret, GetLastError());
    if (ret)
    {
        //�ļ����Ǳ������ˣ�rcΪtrue
        // �����ݱ�����cache�У������ϵͳ��Ϊ�����Ժܿ��ٵ�ȡ�����ݣ�rcΪtrue
    }
    else
    {
        if (GetLastError() == ERROR_IO_PENDING)
        {
            //��������ERROR_IO_PENDING,����ζ�Ŷ��ļ��Ĳ������ڽ�����
            //�Ⱥ�ֱ���ļ�����
            //WaitForSingleObject(hFile, INFINITE);
            //rc = GetOverlappedResult(hFile, &overlap, &numread, FALSE);
            //������������ɵĹ���������һ�����Ĺ��ܵȼۣ�
            // GetOverlappedResult(hFile,&overlap,&numread,TRUE);
        }
        else
        {
            //������
        }
    }
}

int main(int argc, char* argv[])
{
    // ��ӡ�̺߳�
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%^%l%$] %v");
    vector<string> files;
    cf_findFileFromDir(R"(F:\_DayK)", files);
    //׼���߳�����
#ifdef _DEBUG
    const int NThread = 2;
#else
    const int NThread = std::thread::hardware_concurrency() + 2;
#endif // _DEBUG

    //����һ����ɶ˿�
    HANDLE iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, NThread);
    std::vector<std::thread> thread_handles;
    thread_handles.reserve(NThread);

    //�����߳�
    for (int i = 0; i < NThread; ++i)
        thread_handles.push_back(std::thread([iocp]() { io_thread(iocp); }));

    for (auto& file : files)
    {
        //if (file.rfind(".cpp") != string::npos)   // TODO ��ȫ���ᱨ��
        {
            ReadFile(iocp, file);
        }
    }

    //���������߳�ȥ����
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