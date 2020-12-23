# chrono
学习 [C++11 中的日期和时间库](http://www.cnblogs.com/qicosmos/p/3642712.html)，帖子中有一两处描述欠妥的地方，其他都很棒！

我之前整理的 [C++ 获取系统时间][1]，说和 C++ 无关也可以，毕竟通篇都是 C 的东西。新标准的 `std::chrono` 才算是 C++ 的。

对于 [在 C++11 里实现支持毫秒级的时间戳][2] 的描述深有同感：

> C++11 引入的 date-time utilities 一定程度上 解决了这个问题。之所以说是一定程度是因为需要手动做一些 dirty works，囧rz。
>
> 还有一个麻烦的问题没有解决：这几个东西只能代表物理量，没法做格式化输出。
> 
> 委员会自作聪明的让 `Clock` 提供一个 `to_time_t()` 接口，以便让一个 `time-point` 对象转换成 C-Style 的 `time_t` 。。。（我的 `Clock`，时尚时尚最时尚，计时肯定棒…）去-你-大-爷-啊 =”= 

## 阻塞线程执行函数 `sleep_for`

> The standard **recommends** that a steady clock is used to measure the duration. If an implementation uses a system clock instead, the wait time may also **be sensitive to clock adjustments**. [引用来源][3]

MSVC 就是实现的后者脑残版本。MSVC 版本 `std::this_thread::sleep_for` 对调整本地系统时间敏感！——假设目的是阻塞 N，实际测试，发现将时钟调慢 X 会阻塞 X+N，但将时钟调快没有影响，依旧阻塞 N。大家都认为此现象是 bug，但微软一时半会应该是不会改了（msvc12 时已经有用户提交此问题了，到 msvc2017 这个问题还没修复）。

> If you run `std::this_thread::sleep_for()` and **change the system clock**, then the sleep time will be **erroneous**. The code below demonstrates this (rights of the administrator are needed) :[引用来源][4]

测试项目：test

需要“管理员权限”！

- 在 Debian 8.1 && gcc (Debian 4.9.2-10) 4.9.2 环境下测试，调快或者调慢时钟都不会影响 `sleep_for` 阻塞时长。
- 在 MSVC2015 中测试，调快或者调慢时钟不会影响 `Sleep()` 阻塞时长。

[1]:https://tnie.github.io/2016/11/03/getTime/
[2]:http://ju.outofmemory.cn/entry/236380
[3]:https://en.cppreference.com/w/cpp/thread/sleep_for
[4]:https://developercommunity.visualstudio.com/content/problem/61684/stdthis-threadsleep-for-depends-on-system-time.html
