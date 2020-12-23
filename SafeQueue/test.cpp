#include <thread>
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include "SafeQueue.h"

using namespace std;

threadsafe_queue<string> sq;
volatile bool run = false;

// len 为不计末尾 \0 的字符串长度
// 申请空间应大于 len
void gen_random(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

void fun()
{
    run = true;
    while (run)
    {
        auto item = sq.wait_and_pop();
        cout << *item << endl;
        this_thread::sleep_for(200ms);
    }

}

void fun2(int x)
{
    //while (true)
    {
        char str[10];
        gen_random(str, 9); // 10 -1
        sq.push(str);
        this_thread::sleep_for(chrono::seconds(x));
    }
}

int main()
{
    vector<thread> vt;
    thread tt(fun);
    for (size_t i = 5; i < 10; i++)
    {
        vt.push_back(thread(fun2, i));
    }
    ///////////
    for (size_t i = 0; i < vt.size(); i++)
    {
        vt.at(i).join();
    }
    run = false;
    sq.push("");
    tt.join();

    return 0;
}