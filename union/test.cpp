#include <spdlog\spdlog.h>

union More
{
    bool sub{ false };  // ֻ�� sub �������ڳ�ʼֵʱ��More ӵ��Ĭ�Ϲ��캯��
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