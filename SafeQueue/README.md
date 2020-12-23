# threasafe_queue

代码摘抄自 [《C++ Concurrency in Action》][1] 一书的 4.1.2 节。具体的实现细节有以下几个疑问：

1. 为什么 `front()` 和 `pop()` 要封装到单一函数中？
2. `push(T value)` 接口为什么使用 `const T & value`？
3. `try_pop()` 函数为什么返回指针？

还有一个设计思路的疑问：为什么用复合（has-a)而不是继承（is-a)？相关思考不知能否通过复习《Effective C++》获得

- 条款32：确定你的 `public` 继承塑模出 is-a 关系
- 条款38：通过复合塑模出 has-a 或“根据某物实现出”
- 条款39：明智而审慎地使用 `private` 继承


[1]:https://book.douban.com/subject/4130141/