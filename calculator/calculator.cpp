// calculator.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <gtest/gtest.h>
#include "calculator001.h"

using namespace c1;

TEST(Calculator, add)
{
    EXPECT_EQ(2, calculator("1 + 1"));
    EXPECT_DOUBLE_EQ(2, calculator("1.3 +0.7"));
}

TEST(Calculator, sub)
{
    EXPECT_EQ(2, calculator("3 - 1"));
    EXPECT_DOUBLE_EQ(2, calculator("2.3 -0.29999999999999999"));
}

TEST(Calculator, multi)
{
    EXPECT_EQ(2, calculator(".5*4"));
    EXPECT_DOUBLE_EQ(2, calculator(".49999999999999999999*4"));
}

TEST(Calculator, divide)
{
    EXPECT_EQ(2, calculator("4 /2"));
    EXPECT_THROW(calculator("4 /0"), DivideZero);
}

TEST(Calculator, invlide)
{
    EXPECT_ANY_THROW(calculator("123"));
    EXPECT_ANY_THROW(calculator("12@12"));
    EXPECT_ANY_THROW(calculator("fjeoig"));
}

TEST(Calculator, cut)
{
    EXPECT_EQ(calculator("10.2/2="), 5.1);
    EXPECT_EQ(calculator("10.2/2+1"), 5.1);
    EXPECT_EQ(calculator("10.2/2abc"), 5.1);
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
