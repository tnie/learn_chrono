#include "test.h"
#include <memory>
using namespace  std;
int main()
{
    Blob* pb = new Blob();
    Observer* po = new Observer(pb, "��");
    pb->attach(po);
    pb->change(10);
    {
        Observer* po = new Observer(pb, "ë��");
        pb->attach(po);
        pb->change(20);
        delete po;
    }
    pb->change(30);
    delete po;

    return 0;
}
