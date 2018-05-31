#pragma once
#include <string>
#include "Date.h"
#include "Address.h"
class Person
{
public:
    Person();
    ~Person();

private:
    std::string m_name;
    Date m_birthday;
    Address m_address;
};

