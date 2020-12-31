#include <spdlog\spdlog.h>

union More
{
    bool sub{ false };  // 只有 sub 存在类内初始值时，More 拥有默认构造函数
    struct
    {
        time_t endtime /*= 0*/;
        int count /*= 0*/;
    };
};

void info(More more)
{
    spdlog::info("");
    spdlog::info("sub is {}", more.sub);
    spdlog::info("endtime is {}", more.endtime);
    spdlog::info("count is {}", more.count);
}

int main(void)
{
    More more;
    more.endtime = 1557185;
    info(more);
    more.sub = true;
    info(more);
    return 0;
}