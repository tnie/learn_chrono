#pragma once
#include <vector>

class Observer;
class Blob
{
public:
    Blob() {};
    ~Blob() {};

    int attach(const Observer* ob);
    int notify();
    int change(int c);
    int status() const;
private:
    std::vector<const Observer*> m_observers;
    int m_status;
};

class Observer
{
public:
    Observer(const Blob* m);
    ~Observer() {};

    void update() const;

private:
    const Blob* m_blob;
};