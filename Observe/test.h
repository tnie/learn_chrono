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
    Observer(const Blob* m);
    ~Observer();

    void update() const;

private:
    const std::string m_prefix = "##";
    const Blob* m_blob;
};