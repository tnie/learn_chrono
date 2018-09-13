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

//Person::Person(const Person & rhs)
//{
//    *m_pImpl = *rhs.m_pImpl;
//}


Person::Person(Person && rhs)
    :m_pImpl(std::move(rhs.m_pImpl))
{
    // std::move �������ƶ��κζ�������Ψһ�Ĺ����ǽ�һ����ֵǿ��ת��Ϊ��ֵ���ã��̶�����ͨ����ֵ����ʹ�ø�ֵ���������ƶ����塣
    // ��ʵ���Ͻ���std::move ������ͬ��һ������ת����static_cast<T&&>(lvalue);
}

Person::~Person() = default;  // Ҳ����


