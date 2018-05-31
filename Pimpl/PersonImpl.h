#pragma once
#include <string>
#include "Date.h"
#include "Address.h"
#include "Person.h"

class Person::PersonImpl
{
public:
    PersonImpl();
    ~PersonImpl();
private:
    std::string m_name;
    Date m_birthday;
    Address m_address;
};

