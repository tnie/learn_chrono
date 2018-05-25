#include "test.h"

int main()
{
    Blob blob;
    blob.attach(&Observer(&blob));
    blob.attach(&Observer(&blob));
    blob.attach(&Observer(&blob));
    blob.change(10);
    return 0;
}
