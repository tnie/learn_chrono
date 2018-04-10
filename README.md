# chrono
学习 [C++11 中的日期和时间库](http://www.cnblogs.com/qicosmos/p/3642712.html)，帖子中有一两处描述欠妥的地方，其他都很棒！

我之前整理的 [C++ 获取系统时间][1]，说和 C++ 无关也可以，毕竟通篇都是 C 的东西。新标准的 `std::chrono` 才算是 C++ 的。

对于 [在 C++11 里实现支持毫秒级的时间戳][2] 的描述深有同感：

> C++11引入的date-time utilities 一定程度上 解决了这个问题。之所以说是一定程度是因为需要手动做一些dirty works，囧rz。
>
> 还有一个麻烦的问题没有解决：这几个东西只能代表物理量，没法做格式化输出。
> 
> 委员会自作聪明的让Clock提供一个 to_time_t 接口，以便让一个time-point对象转换成C-Style的 time_t 。。。（我的Clock，时尚时尚最时尚，计时肯定棒…）去-你-大-爷-啊 =”= 

[1]:https://tnie.github.io/2016/11/03/getTime/
[2]:http://ju.outofmemory.cn/entry/236380
