#include "Person.h"
#include <vector>
#include <map>
#include <string>
//#define  CLEAR_ERR_MSG
using namespace  std;
// @Person �Ŀͻ�
// ��ȫ�� Date/Address �Լ� Person��ʵ��ϸĿ����
int main()
{
    Person niel;
#ifdef CLEAR_ERR_MSG
    std::vector<Person> family;
    // error C2280: ��Person::Person(const Person &)��: ����������ɾ���ĺ���
    family.push_back(niel);
    // error C2280: ��std::pair<const char *,Person>::pair(const std::pair<const char *,Person> &)��: ����������ɾ���ĺ���
    auto item = std::make_pair("father", niel);
#else
    std::map<string, Person> family;
    // error C2664: �޷������� 1 �ӡ�initializer list��ת��Ϊ��std::pair<const _Kty,_Ty> &&��
    // note: ԭ������: �޷��ӡ�initializer list��ת��Ϊ��std::pair<const _Kty,_Ty>��
    // note: �޹��캯�����Խ���Դ���ͣ����캯�����ؾ��߲���ȷ
    family.insert({"father", niel});
#endif // CLEAR_ERR_MSG

    // ��������Ϊ��ʽ�����˹���or���������� Person �޿������캯��
    // ���ԣ�������Ϊ��Ա�� pair Ҳδ�ϳɿ������캯��
    return 0;
}