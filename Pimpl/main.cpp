#include "Person.h"
#include <vector>
#include <map>
#include <string>
using namespace  std;
// @Person 的客户
// 完全与 Date/Address 以及 Person的实现细目分离

void test(const Person & person)
{
    std::vector<Person> family;
    // TODO 为什么还是匹配的拷贝构造呢？——见 README # 移动构造和常量
    // error C2280: “Person::Person(const Person &)”: 尝试引用已删除的函数
    //family.push_back(std::move(person));
}

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