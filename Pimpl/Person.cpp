#include "Person.h"
#include "PersonImpl.h"



Person::Person():m_pImpl(std::make_shared<PersonImpl>())
{
}


Person::~Person()
{
}


