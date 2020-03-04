#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <gtest\gtest.h>

using namespace std;
//using namespace chrono;

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class DurationTest : public ::testing::Test
{
public:
    DurationTest(): twoseconds_(2)
    {

    }
    static void SetUpTestSuite() {}
    static void TearDownTestSuite()
    {
        auto str = R"(
*****************************************************************************
duration 的概念较为独立，但 time_point 和 clock 则互相引用，难以划清明显的边界。
    duration 只要区分数值、单位就很容易理解。
*****************************************************************************
)";
        cout << str << endl;
    }
    void SetUp() override {}
    void TearDown() override {}
//private:
    const chrono::duration<int> twoseconds_;
};

TEST_F(DurationTest, CopyCtor)
{
    ASSERT_EQ(twoseconds_.count(), 2) << "2s has " << twoseconds_.count() << " seconds.";
    //auto twoseconds_ = chrono::seconds(2);
    chrono::milliseconds alias = twoseconds_;    // 这都行-拷贝构造可以
    ASSERT_EQ(alias.count(), 2000) << "2s has " << alias.count() << " milliseconds.";
    alias = twoseconds_;     // 低精度赋值给高精度可以
    ASSERT_EQ(twoseconds_, alias);
    //twoseconds_ = alias;     // 高精度赋值给低精度必须显式转换
    auto twoseconds = chrono::duration_cast<chrono::seconds>(alias);
    EXPECT_EQ(twoseconds, alias);
}

TEST_F(DurationTest, Arithmetic)
{
    auto alias = twoseconds_ * 2;    // 这都行
    ASSERT_EQ(alias.count(), 4) << "4s has " << alias.count() << " seconds.";
    alias = twoseconds_ / 2;    // 这都行
    ASSERT_EQ(alias.count(), 1) << "1s has " << alias.count() << " seconds.";
    alias = twoseconds_ / 4;    // 这都行，结果是错误的
    ASSERT_EQ(alias.count(), 0) << "0.5s has " << alias.count() << " seconds.";

    /*估计也就是个先乘后除，先除后乘的问题*/
    auto alias2 = chrono::duration_cast<chrono::milliseconds>(twoseconds_) / 4;
    ASSERT_EQ(alias2.count(), 500) << "0.5s has " << alias2.count() << " milliseconds.";
    chrono::milliseconds diff = alias - twoseconds_;
    ASSERT_EQ(diff.count(), -2000) << "diff(milli) is: " << diff.count();
    diff = alias2 - twoseconds_;
    ASSERT_EQ(diff.count(), -1500) << "diff(milli) is: " << diff.count();
}

TEST_F(DurationTest, HalfSecond)
{
    // 自定义时间间隔：半秒
    typedef chrono::duration<double, ratio<1, 2>> halfseconds;
    auto var = halfseconds(2.5);    // 1.25 秒
    ASSERT_EQ(var.count(), 2.5) << "1.25s has " << var.count() << " halfseconds";
    //alias = var; // 需要显示转换
    auto alias = chrono::duration_cast<chrono::milliseconds> (var);
    ASSERT_EQ(alias.count(), 1250) << "1.25s has " << alias.count() << " milliseconds";
}

namespace il
{
    // 自定义时间间隔：半秒
    typedef chrono::duration<double, ratio<1, 2>> halfseconds;
    inline constexpr halfseconds operator "" hs(long double x)
    {
        return halfseconds(x);
    }
}

TEST_F(DurationTest, Literals)
{
    auto twoseconds = 2s;
    auto alias = chrono::duration_cast<chrono::milliseconds>(twoseconds / 4);
    ASSERT_EQ(alias.count(), 0) << "0.5s has " << alias.count() << " milliseconds.";

    auto ts = 2.s;     //chrono::duration<double>(2);
    alias = chrono::duration_cast<chrono::milliseconds>(ts / 4);
    ASSERT_EQ(alias.count(), 500) << "0.5s has " << alias.count() << " milliseconds.";

    using namespace il;
    auto var = 2.5hs;    // 1.25 秒
    ASSERT_EQ(var.count(), 2.5) << "1.25s has " << var.count() << " halfseconds";
}

TEST(TIME_POINT_CLOCK, Sleep)
{
    chrono::time_point<chrono::steady_clock> t1 = chrono::steady_clock::now();
    this_thread::sleep_for(2s);
    auto t2 = chrono::steady_clock::now();
    chrono::steady_clock::duration diff = t2 - t1;
    ASSERT_NE(diff.count(), 2e9) << "diff(nano) is: " << diff.count();  // 2s 并不是严格意义上的 2*10^9 纳秒

    cout << setw(20) << "now(nano) is: " << t2.time_since_epoch().count() << endl;  //  TODO steady_clock 不是从 1970 年算起？
    chrono::steady_clock;   // 没有 to_time_t()/fromw_time_t()
    chrono::system_clock::now();
}

TEST(TIME_POINT_CLOCK, Epoch)
{
    auto t3 = chrono::system_clock::now();  // 查看底层实现，发现 system_clock 比 steady_clock 精度低100 倍
    cout << setw(20) << "now(/nano*100) is: " << t3.time_since_epoch().count() << endl;
    cout << setw(20) << "now(time_t/s) is: " << chrono::system_clock::to_time_t(t3) << endl;

    typedef chrono::duration<int, ratio<60 * 60 * 24>> days_type;
    //days_type days = t3.time_since_epoch();     // 降低精度需要显式转换
    days_type days = chrono::duration_cast<days_type>(t3.time_since_epoch());
    cout << setw(20) << "now(days) is: " << days.count() << endl;
    auto days_point = chrono::time_point_cast<days_type>(t3);   // 与上述等价
    cout << setw(20) << "now(days) is: " << days_point.time_since_epoch().count() << endl;
    ASSERT_EQ(days.count(), days_point.time_since_epoch().count());
}

