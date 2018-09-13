#include "Person.h"
#include <vector>
#include <map>
#include <string>
//#define  CLEAR_ERR_MSG
using namespace  std;
// @Person 的客户
// 完全与 Date/Address 以及 Person的实现细目分离
int main()
{
    Person niel;
#ifdef CLEAR_ERR_MSG
    std::vector<Person> family;
    // error C2280: “Person::Person(const Person &)”: 尝试引用已删除的函数
    family.push_back(niel);
    // error C2280: “std::pair<const char *,Person>::pair(const std::pair<const char *,Person> &)”: 尝试引用已删除的函数
    auto item = std::make_pair("father", niel);
#else
    std::map<string, Person> family;
    // error C2664: 无法将参数 1 从“initializer list”转换为“std::pair<const _Kty,_Ty> &&”
    // note: 原因如下: 无法从“initializer list”转换为“std::pair<const _Kty,_Ty>”
    // note: 无构造函数可以接受源类型，或构造函数重载决策不明确
    family.insert({"father", niel});
#endif // CLEAR_ERR_MSG

    // 分析：因为显式声明了构造or析构，类型 Person 无拷贝构造函数
    // 所以，以其作为成员的 pair 也未合成拷贝构造函数
    return 0;
}