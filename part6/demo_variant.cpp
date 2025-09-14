#include <string>
#include <iostream>
// 一个类型安全的联合体
#include <variant>

using namespace std;

// 用于打印当前活动的类型
struct PrintVisitor {
    void operator ()(int i) { cout << "int: " << i << '\n'; }
    void operator ()(float f) { cout << "float: " << f << '\n'; }
    void operator ()(const string& s) { cout << "str: " << s << '\n'; }
};

int main() {
    variant<int, float, string> intFloatString;
    static_assert(variant_size_v<decltype(intFloatString)> == 3);

    // 默认初始化为第一个可选类型，应该是0
    // 它通过一个可调用对象（如 lambda 或函数对象）对 variant 当前存储的类型安全地执行操作
    visit(PrintVisitor{}, intFloatString);

    // index将显示当前使用的“类型”
    cout << "index = " << intFloatString.index() << endl;
    intFloatString = 100.0f;
    cout << "index = " << intFloatString.index() << endl;
    intFloatString = "hello super world";
    cout << "index = " << intFloatString.index() << endl;

    // 尝试使用get_if：
    if (const auto intPtr = get_if<int>(&intFloatString))
        cout << "int: " << *intPtr << '\n';
    else if (const auto floatPtr = get_if<float>(&intFloatString))
        cout << "float: " << *floatPtr << '\n';

    // holds_alternative检查当前使用的类型是什么
    if (holds_alternative<int>(intFloatString))
        cout << "the variant holds an int!\n";
    else if (holds_alternative<float>(intFloatString))
        cout << "the variant holds a float\n";
    else if (holds_alternative<string>(intFloatString))
        cout << "the variant holds a string\n";

    // try/catch和bad_variant_access
    try {
        auto f = get<float>(intFloatString);
        cout << "float! " << f << '\n';
    }
    catch (bad_variant_access&) {
        cout << "our variant doesn't hold float at this moment...\n";
    }
}

// 一些可能的使用场景：
// 1. 在所有可能为单个字段获取几种类型的地方，比如解析命令行、ini文件、语言解析器等
// 2. 高效表达计算的几种可能结果，比如求方程的根
// 3. 错误处理——例如，你可以返回variant<Object, ErrorCode>。如果有值可用，就返回Object，否则分配一些错误码
// 4. 有限状态机（Finite State Machines）
// 5. 无需虚函数表（vtables）和继承的多态性（借助访问者模式）