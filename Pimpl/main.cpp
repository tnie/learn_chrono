#include "Person.h"
#include <vector>
#include <map>
#include <string>
using namespace  std;
// @Person �Ŀͻ�
// ��ȫ�� Date/Address �Լ� Person��ʵ��ϸĿ����
int main()
{
    Person niel;
    /*std::vector<Person> family;
    family.push_back(std::move(niel));*/
    auto item = std::make_pair("father", std::move(niel));
    // Note: ���� niel �Ѿ����Ϸ�������ʹ�� niel �Ǵ�ġ�
    std::map<string, Person> family;
    family.insert(std::move(item));
    Person mu;
    family.insert({"son", std::move(mu)});

    return 0;
}