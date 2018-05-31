#include "Person.h"
#include <string>
#include "Date.h"
#include "Address.h"

//Person::~Person() = default;  // Ҳ����

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


Person::~Person() = default;  // Ҳ����


