#include "Person.h"
#include <vector>
#include <map>
#include <string>
using namespace  std;
// @Person 的客户
// 完全与 Date/Address 以及 Person的实现细目分离
int main()
{
    Person niel;
    /*std::vector<Person> family;
    family.push_back(std::move(niel));*/
    auto item = std::make_pair("father", std::move(niel));
    // Note: 对象 niel 已经不合法，后面使用 niel 是错的。
    std::map<string, Person> family;
    family.insert(std::move(item));
    Person mu;
    family.insert({"son", std::move(mu)});

    return 0;
}