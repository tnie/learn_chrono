#pragma once
#include <memory>

class Person
{
public:
    Person();
    //~Person();

private:
    class PersonImpl;
    std::unique_ptr<PersonImpl> m_pImpl;
};

