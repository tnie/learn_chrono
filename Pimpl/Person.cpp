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
    // ��ֵ���ñ�������������ֵ������Ҫ�󶨵�������ֵ���ò��������أ��ͱ���ת������ֵ��
    // �����ƶ����캯�����ƶ���ֵ��������͵�ʹ�� std::move ��ԭ��
}

Person::~Person() = default;  // Ҳ����


