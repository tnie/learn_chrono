#pragma once
#include <iostream>
#include <type_traits>
#include "my_traits.h"

template<class M>
class MyTmplte
{
public:
    //void process(size_t times, const T& t);  // ERR �޷����������������е�����ƥ��
    template<class T>
    std::enable_if_t<std::is_integral<T>::value>
        process(size_t times, const T& t);

    /*std::enable_if_t<(my_traits<T>::type == mytype::is_char_pointer) ||
        (my_traits<T>::type == mytype::is_std_string)>
        process(size_t times, const T& t);*/

    template<class T>
    std::enable_if_t<false>
        process(size_t times, const T& t);      // ���󣺲�������
    MyTmplte() = default;
};

template<class M>
template<class T>
inline std::enable_if_t<std::is_integral<T>::value>
MyTmplte<M>::process(size_t times, const T& t)
{
    for (size_t i = 0; i < times; i++)
    {
        std::cout << t << "/";
    }
    std::cout << std::endl;
}

//template<class T>
////std::enable_if_t<(my_traits<T>::type == mytype::is_char_pointer) ||
////(my_traits<T>::type == mytype::is_std_string)>
//std::enable_if_t<my_traits<T>::value || my_traits<T>::value>
//MyTmplte<T>::process(size_t times, const T& t)
//{
//    std::string str(t);
//    if (str.length() <= times)
//    {
//        cout << str << endl;
//    }
//    else
//    {
//        cout << str.substr(0, times) << endl;
//    }
//}
