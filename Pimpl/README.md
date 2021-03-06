demo 依据《Effective C++》条款 31，以及《Effective Modern C+.
+》[条款 22][1] 编写。

# 移动语义、移动构造

[https://zh.cppreference.com/w/cpp/utility/move](https://zh.cppreference.com/w/cpp/utility/move)
> `std::move()` 用于指示对象 t 可以“被移动”，即允许从 t 到另一对象的有效率的资源传递。
> 特别是， `std::move()` 生成标识其参数 t 的 [亡值表达式][2]。它准确地等价于到右值引用类型的 `static_cast` 。

> 以右值参数（如临时对象的纯右值或如 `std::move()` 所产生者的**亡值**之一）调用函数时，重载决议选择接受右值引用参数的版本（包含移动构造函数、移动赋值运算符及常规成员函数，如 `std::vector::push_back()` ）。若参数标识一个占有资源的对象，则这些重载拥有移动参数所保有的任何资源的选择，但不强求如此。

[`std::move()` 并不会移动对象][3]，真正的移动操作在移动构造函数（或移动赋值函数或其他常规函数，如 `std::vector::push_back()`），`std::move()` 就是一个类型转换。

[条款23：理解 `std::move` 和 `std::forward`][4]

> 第一，假如你想对象能够被移动，不要声明对象为 `const`，在 `const` 对象上的移动操作默默的被转换成了拷贝操作。第二，`std::move()` 不仅不移动任何东西，甚至不能保证被转换的对象可以被移动。唯一可以确认的是应用 `std::move()` 的对象结果是个右值。

## 移动构造和常量

[https://stackoverflow.com/questions/28595117/why-can-we-use-stdmove-on-a-const-object](https://stackoverflow.com/questions/28595117/why-can-we-use-stdmove-on-a-const-object)

In the book 'Effective Modern C++' by Scott Meyers, he gives an example:

```cpp
class Annotation {
public:
    explicit Annotation(const std::string text)
     : value(std::move(text)) //here we want to call string(string&&),
                              //but because text is const, 
                              //the return type of std::move(text) is const std::string&&
                              //so we actually called string(const string&)
                              //it is a bug which is very hard to find out
private:
    std::string value;
};
```

> here we want to call `string(string&&)`,
> but because text is `const`, 
> the return type of `std::move(text)` is `const std::string&&`
> so we actually called `string(const string&)`
> it is a bug which is **very hard to find out**

某个大神的回复：

> There's a trick here you're overlooking, namely that `std::move(cat)` doesn't actually move anything. It merely tells the compiler to **try to** move. However, since your class has no constructor that accepts a `const CAT&&`, it will instead use the implicit `const CAT&` copy constructor, and safely copy. No danger, no trap. If the copy constructor is disabled for any reason, you'll get a compiler error.
> 
> Additionally, such a bug also occurs for non-const objects that don't have move constructors, 

# 实现 pImpl 推荐使用 `shared_ptr`，而非 `unique_ptr` 

使用 `unique_ptr` 智能指针需要处理较多的脏活（在 commit message 中依次记录了）：

- 需要分别在头文件和源文件**显式声明、定义析构**；
- 如有需要，需显式声明**拷贝构造**、赋值（因为成员变量 `unique_ptr` 不支持拷贝构造和赋值）；
- 如有需要，**移动构造**也要显式定义；

但使用 `shared_ptr`，上述提到的三点可以全然不理。

[1]:https://blog.csdn.net/big_yellow_duck/article/details/52351729
[2]:https://zh.cppreference.com/w/cpp/language/value_category
[3]:https://blog.csdn.net/weixin_36888577/article/details/80787782
[4]:https://blog.csdn.net/coolmeme/article/details/44459999
