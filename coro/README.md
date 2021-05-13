https://devblogs.microsoft.com/oldnewthing/20191209-00/?p=103195

> Therefore, it is important that your awaiter not use its this pointer once it has arranged for the handle to be invoked somehow, because the this pointer may no longer be valid.

最简单的 awaiter + 最简单的 promise = 最简单的协程

个人的 [学习总结](https://tnie.github.io/2021/04/02/coroutine/)