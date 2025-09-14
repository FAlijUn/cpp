#include <any>
#include <iostream>
#include <map>
#include <string>
#include <cassert>

int main() {
    std::any a(12);
    // 设置任意值:
    a = std::string("Hello!");
    a = 16;
    // 读取值:
    // 我们可以将其作为int读取
    std::cout << std::any_cast<int>(a) << '\n ';
    // 但不能作为string读取:
    try {
        std::cout << std::any_cast<std::string>(a) << '\n ';
    }
    catch (const std::bad_any_cast& e) {
        std::cout << e.what() << '\n ';
    }
    // 重置并检查它是否包含值:
    a.reset();
    if (!a.has_value()) {
        std::cout << "a is empty!" << '\n ';
    }
    // 你可以在容器中使用它:
    std::map<std::string, std::any> m;
    m["integer"] = 10;
    m["string"] = std::string("Hello World");
    m["float"] = 1.0f;
    for (auto &[key, val] : m) {
        if (val.type() == typeid(int))
            std::cout << "int: " << std::any_cast<int>(val) << '\n ';
        else if (val.type() == typeid(std::string))
            std::cout << "string: " << std::any_cast<std::string>(val) << '\n ';
        else if (val.type() == typeid(float))
            std::cout << "float: " << std::any_cast<float>(val) << '\n ';
    }
    return 0;

    // 默认初始化:
    std::any a;
    assert(!a.has_value());
    // 用对象初始化:
    std::any a2{10}; // int
    // 原位构造:
    std::any a5{std::in_place_type<std::string>, "Hello World"};
    // make_any
    std::any a6 = std::make_any<std::string>("Hello World");
    // std::any有一个名为std::make_any的工厂函数，返回
    // return std::any(std::in_place_type<T>, std::forward<Args>(args)...);
    auto b = std::make_any<std::string>("hello");

    std::any var = 10;
    // 读取访问:
    auto a = std::any_cast<int>(var);
    // 通过引用进行读写访问:
    std::any_cast<int&>(var) = 11;
    // 通过指针进行读写访问:
    int* ptr = std::any_cast<int>(&var);
    *ptr = 12;

}

// 一些可能的场景：
// 在库中 —— 当库类型必须存储或传递任意数据，却不知道可用的类型集合时；
// 文件解析 —— 如果你确实无法指定受支持的类型；
// 消息传递；
// 与脚本语言的绑定；
// 实现脚本语言的解释器；
// 用户界面 —— 控件可能需要存储任意数据；
// 编辑器中的实体。
