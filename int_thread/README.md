
[关于C++多线程程序中简单类型(int/bool)的安全性][1]

对于简单类型（单字节）的读写 [Is volatile a proper way to make a single byte atomic in C/C++?][2]，虽然在某些平台保证底层操作的原子性，但涉及多核时问题又变得更复杂。从 C++ 标准出发，在其引入线程模型之前不涉及多线程，但在其引入线程模型之后，其未约定内置类型的线程安全，所以作为使用者，不做任何假设。

所以，在多线程中使用内置类型，需要引入其他方法保证其操作原子性。

对内置类型的线程安全特性，不做任何假设。

[1]:https://blog.csdn.net/superarhow/article/details/18009667
[2]:https://stackoverflow.com/questions/4936289/is-volatile-a-proper-way-to-make-a-single-byte-atomic-in-c-c