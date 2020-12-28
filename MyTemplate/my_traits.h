#pragma once
#include <string>

enum mytype :char
{
    is_char_pointer,
    is_std_string,
    unknow
};

template<class T>
struct my_traits
{
    static constexpr mytype type = mytype::unknow;
    static constexpr bool value = false;
};

template<>
struct my_traits<char*>
{
    static const mytype type = mytype::is_char_pointer;
    static constexpr bool value = true;
};

template<>
struct my_traits<std::string>
{
    static const mytype type = mytype::is_std_string;
    static constexpr bool value = true;
};
