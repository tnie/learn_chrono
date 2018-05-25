#include "test.h"

int main()
{
    Blob blob;
    Observer ob1(&blob);
    blob.attach(&ob1);
    blob.attach(&Observer(&blob));
    blob.attach(&Observer(&blob));
    blob.change(10);
    return 0;
}
