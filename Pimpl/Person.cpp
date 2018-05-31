#include "Person.h"
#include <string>
#include "Date.h"
#include "Address.h"

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

Person::Person():m_pImpl(std::make_shared<PersonImpl>())
{
}


//Person::~Person()
//{
//}


