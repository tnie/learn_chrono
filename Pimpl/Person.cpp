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
    // 右值引用变量的名称是左值，而若要绑定到接受右值引用参数的重载，就必须转换到亡值，
    // 此乃移动构造函数与移动赋值运算符典型地使用 std::move 的原因
}

Person::~Person() = default;  // 也可以


