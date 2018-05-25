#pragma once
#include <vector>
#include <string>
class Observer;
class Blob
{
public:
    Blob() {};
    ~Blob();

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
    Observer(const Blob* m, const std::string& name);
    ~Observer();

    void update() const;

private:
    const std::string m_name;
    const Blob* m_blob;
};