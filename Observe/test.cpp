#include "test.h"
#include <iostream>

using namespace std;
Blob::~Blob() { cout << "blob dctor" << endl; }
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

Observer::Observer(const Blob* m, const std::string& name) :m_blob(m), m_name(name)
{

}

Observer::~Observer()
{
    cout << "observer[" << m_name << "] dctor" << endl;
}

void Observer::update() const
{
    cout << "[" << m_name << "]";
    cout << "status value: " << m_blob->status() << endl;
}
