#include "test.h"
#include <iostream>

using namespace std;
int Blob::attach(const Observer * ob)
{
    m_observers.push_back(ob);
    return m_observers.size();
}

inline int Blob::notify()
{
    for each (const auto var in m_observers)
    {
        var->update();
    }
    return m_observers.size();
}

inline int Blob::change(int c)
{
    m_status = c;
    return notify();
}

inline int Blob::status() const
{
    return m_status;
}

Observer::Observer(const Blob * m) :m_blob(m)
{

}

inline void Observer::update() const
{
    cout << "status value: " << m_blob->status() << endl;
}
