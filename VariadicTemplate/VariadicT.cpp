#include <iostream>

using namespace std;

template<typename T, typename... Args>
void foo(const T & t, const Args& ... rest)
{
    cout << sizeof...(Args) << endl;
    cout << sizeof...(rest) << endl;
}

int main()
{
    struct F
    {

    } f;
    foo(1, 2.2, "hah", 3.1, 2.2, f);
    return 0;
}

