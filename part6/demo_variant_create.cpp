#include <string>
#include <iostream>
#include <variant>

class NotSimple {
public:
    NotSimple(int, float) {}
};

int main()
{
    // 默认初始化：（第一个类型必须有默认构造函数）
    std::variant<int, float> intFloat;
    std::cout << intFloat.index() << ", val: " << std::get<int>(intFloat) << '\n';

    // std::variant<NotSimple, int> cannotInit; // 错误
    // std::monostate 是一个空类型，常用于 std::variant 的第一个模板参数，表示“无值”或“默认状态”。
    // 让 std::variant 总是有一个有效的初始状态（即使其它类型没有默认构造函数）。
    // 便于用 std::visit 统一处理“未赋值”或“空”的情况
    std::variant<std::monostate, NotSimple, int> okInit;
    std::cout << okInit.index() << '\n';

    // 传递一个值：
    std::variant<int, float, std::string> intFloatString { 10.5f };
    std::cout << intFloatString.index()
            << ", value " << std::get<float>(intFloatString) << '\n';
    
    // 存在歧义
    // double可能转换为float或int，所以编译器无法决定
    //std::variant<int, float, std::string> intFloatString { 10.5 };
    // 使用in_place解决歧义
    std::variant<long, float, std::string> longFloatString {
        std::in_place_index<1>, 7.6 // double!
    };
    std::cout << longFloatString.index() << ", value "
          << std::get<float>(longFloatString) << '\n';

    // 对复杂类型使用in_place
    std::variant<std::vector<int>, std::string> vecStr {
        std::in_place_index<0>, { 0, 1, 2, 3 }
    };
    std::cout << vecStr.index() << ", vector size "
            << std::get<std::vector<int>>(vecStr).size() << '\n';
    
    // 从其他变体进行拷贝初始化：
    std::variant<int, float> intFloatSecond { intFloat };
    std::cout << intFloatSecond.index() << ", value "
            << std::get<int>(intFloatSecond) << '\n';


    std::variant<int, float, std::string> intFloatString { "Hello" };
    intFloatString = 10; // 现在是int类型
    intFloatString.emplace<2>(std::string("Hello")); // 现在又变回string类型
    // std::get返回一个引用，所以你可以更改值:
    std::get<std::string>(intFloatString) += std::string(" World");

    intFloatString = 10.1f;
    if (auto pFloat = std::get_if<float>(&intFloatString); pFloat) 
    *pFloat *= 2.0f;

    std::variant<int, float, std::string> myVariant;
    std::visit(
        overload {
            [](const int& i) { std::cout << "int: " << i; },
            [](const std::string& s) { std::cout << "string: " << s; },
            [](const float& f) { std::cout << "float: " << f; }
        },
        myVariant );


}

// 默认情况下，变体对象使用第一个类型进行初始化
// 如果该类型没有默认构造函数，无法进行初始化，你会得到一个编译错误
// 在这种情况下，你可以使用std::monostate作为第一个类型
// std::monostate允许你构建一个 “无值” 的变体，因此它的行为可以类似于std::optional
// 你可以使用一个值进行初始化，然后会使用最匹配的类型
// 如果存在歧义，你可以使用std::in_place_index版本显式指定应该使用的类型
// std::in_place还允许你创建更复杂的类型，并向构造函数传递更多参数


