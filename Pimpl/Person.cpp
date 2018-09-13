#include "Person.h"
#include <string>
#include "Date.h"
#include "Address.h"

//Person::~Person() = default;  // 也可以

class Person::PersonImpl
{
public:
    /*PersonImpl();
    ~PersonImpl();*/
private:
    std::string m_name;
    Date m_birthday;
    Address m_address;
};

Person::Person():m_pImpl(std::make_unique<PersonImpl>())
{
}

Person::Person(const Person & rhs)
{
    *m_pImpl = *rhs.m_pImpl;
}


Person::~Person() = default;  // 也可以


