#include "test.h"

#include <string>
#include <iostream>

using namespace std;

int main()
{
    MyTmplte<int>().process(2, 33);
    MyTmplte<char>().process(2, '$');
    /*MyTmplte<char*>().process(2, "abcn");
    MyTmplte<string>().process(10, "abcn");*/
    return 0;
}