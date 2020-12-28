#include <iostream>
#include "add.h"
using namespace std;

void sum(string err, int sum) {
    if (err.empty())
    {
        cout << "sum: " << sum << endl;
    }
    else
    {
        cout << err << endl;
    }
}

int main()
{
    cout << "main()" << endl;

    add_callback(2, 3, ::sum);
    add_callback(-2, 3, ::sum);
    add_callback(22, 3, ::sum);
    try
    {
        int sum = add(2, 3);
        cout << "2+3=" << sum << endl;

        sum = add(-2, 3);
        cout << "3-2=" << sum << endl;
        sum = add(21, 3);
        cout << "21+3=" << sum << endl;

    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
    }
    return 0;
}