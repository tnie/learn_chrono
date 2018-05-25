#include "test.h"
#include <memory>
using namespace  std;
int main()
{
    Blob blob;
    Observer ob1(&blob);
    blob.attach(&ob1);
    shared_ptr<char> ptr(new char[100000], [](char* p) {delete[]p; });
    blob.attach(&Observer(&blob));
    blob.attach(&Observer(&blob));
    blob.change(10);
    return 0;
}
