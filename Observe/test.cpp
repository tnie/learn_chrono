#include "test.h"
#include <iostream>

using namespace std;
int Blob::attach(const Observer * ob)
{
    m_observers.push_back(ob);
    return m_observers.size();
}

int Blob::notify()
{
    for each (const auto var in m_observers)
    {
        // TODO 对象已销毁
        var->update();
    }
    return m_observers.size();
}

int Blob::change(int c)
{
    m_status = c;
    return notify();
}

int Blob::status() const
{
    return m_status;
}

Observer::Observer(const Blob * m) :m_blob(m)
{

}

void Observer::update() const
{
    cout << m_prefix << "status value: " << m_blob->status() << endl;
}
