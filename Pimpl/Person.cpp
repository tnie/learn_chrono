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

//Person::Person(const Person & rhs)
//{
//    *m_pImpl = *rhs.m_pImpl;
//}


Person::Person(Person && rhs)
    :m_pImpl(std::move(rhs.m_pImpl))
{
    // std::move 并不能移动任何东西，它唯一的功能是将一个左值强制转化为右值引用，继而可以通过右值引用使用该值，以用于移动语义。
    // 从实现上讲，std::move 基本等同于一个类型转换：static_cast<T&&>(lvalue);
}

Person::~Person() = default;  // 也可以


