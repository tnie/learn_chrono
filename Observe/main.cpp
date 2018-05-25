#include "test.h"

int main()
{
    Blob blob;
    blob.attach(&Observer(&blob));
    blob.attach(&Observer(&blob));
    blob.attach(&Observer(&blob));
    return 0;
}
