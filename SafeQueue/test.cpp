#include <thread>
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include "SafeQueue.h"

using namespace std;

SafeQueue<string> sq;

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
    while (true)
    {
        auto item = sq.dequeue();
        cout << item << endl;
        this_thread::sleep_for(200ms);
    }

}

void fun2(int x)
{
    while (true)
    {
        char str[10];
        gen_random(str, 10);
        sq.enqueue(str);
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
    tt.join();

    return 0;
}