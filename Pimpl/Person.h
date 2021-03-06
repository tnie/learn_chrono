#pragma once
#include <memory>

class Person
{
public:
    Person();
    //Person(const Person& rhs);
    Person(Person && rhs);
    ~Person();
    //~Person() = default;  // error C2338 too:

private:
    class PersonImpl;
    std::unique_ptr<PersonImpl> m_pImpl;
};

