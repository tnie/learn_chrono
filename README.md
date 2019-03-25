# PassKeyIdiom
传递秘钥惯用法

代码摘自 [Passkey Idiom and Better Friendship in C++](https://www.spiria.com/en/blog/desktop-software/passkey-idiom-and-better-friendship-c/)

博主给出的例子 https://github.com/fmayrand/passkey-idiom-example

博文评论也值得一看。

## 需要强调的坑

[Because C++ is C++, there are a few gotchas to avoid:](https://stackoverflow.com/a/3218920/6728820)
- the copy constructor has to be user-defined, otherwise it is `public` by default
- the default constructor has to be user-defined, otherwise it is `public` by default
- the default constructor has to be manually defined, because `= default` would allow aggregate initialization to bypass the manual user-defined default constructor (and thus allow any type to get an instance)

```cpp
#include <cstdio>
class Test
{
    Test() = default;
public:
    void hello() const { printf("Hello world.\n"); }
};

int main()
{
    //Test acb;   //error C2248: “Test::Test”: 无法访问 private 成员
    Test abc{}; // THIS COMPILES
    abc.hello();
    return 0;
}
```