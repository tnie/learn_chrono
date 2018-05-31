#pragma once
#include <memory>

class PersonImpl;

class Person
{
public:
    Person();
    ~Person();

private:
    std::shared_ptr<PersonImpl> m_pImpl;
};

