#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <sstream>
#include <set>



using namespace std;

mutex mt;
// ��volatile **����**��֤ȫ�����α����Ƕ��̰߳�ȫ��
/*volatile*/ int global1 = 0;

// ++/-- ������ͬʱ�漰��д

void fun1()
{
    for (size_t i = 0; i < 100000; i++)
    {
        //lock_guard<mutex> lg(mt);
        ++global1;
    }

}

void fun2()
{
    for (size_t i = 0; i < 100000; i++)
    {
        //lock_guard<mutex> lg(mt);
        --global1;
    }

}

void fun3()
{
    static int static2;
    for (size_t i = 0; i < 100000; i++)
    {
        //lock_guard<mutex> lg(mt);
        ++static2;
        --static2;
    }
    ostringstream oss;
    // ������ʱ������ static2 ��������Ρ��ں�����̬�������̶߳�дҲ�ǲ���ȫ��
    oss << "������̬����: " << static2 << endl;
    cout << oss.str();

}

int main()
{
    thread t1(fun1);
    thread t2(fun2);
    t1.join();
    t2.join();
    // ������ʱ������ global1 ��������Ρ���ȫ��ԭ���������̶߳�д�ǲ���ȫ��
    cout << "ȫ��ԭ������: " << global1 << endl;
    thread t31(fun3);
    thread t32(fun3);
    t31.join();
    t32.join();
    return 0;
}