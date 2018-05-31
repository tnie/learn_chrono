#pragma once
class Address
{
public:
    //Address() {};
    // 构造函数和析构函数往往是 inline 函数的糟糕候选人 《Effective C++》 P137
    Address();
    ~Address();
};

