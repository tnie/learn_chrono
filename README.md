demo 依据《Effective C++》条款 31，以及《Effective Modern C+.
+》[条款 22][1] 编写。

# 移动语义、移动构造

[https://zh.cppreference.com/w/cpp/utility/move](https://zh.cppreference.com/w/cpp/utility/move)
> `std::move` 用于指示对象 t 可以“被移动”，即允许从 t 到另一对象的有效率的资源传递。
> 特别是， `std::move` 生成标识其参数 t 的 [亡值表达式][2]。它准确地等价于到右值引用类型的 `static_cast` 。

> 以右值参数（如临时对象的纯右值或如 `std::move` 所产生者的**亡值**之一）调用函数时，重载决议选择接受右值引用参数的版本（包含移动构造函数、移动赋值运算符及常规成员函数，如 `std::vector::push_back` ）。若参数标识一个占有资源的对象，则这些重载拥有移动参数所保有的任何资源的选择，但不强求如此。

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

[1]:https://blog.csdn.net/big_yellow_duck/article/details/52351729
[2]:https://zh.cppreference.com/w/cpp/language/value_category