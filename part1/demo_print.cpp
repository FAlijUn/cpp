#include <iostream>

template <typename T> void linePrinter(const T& x) {
    // if constexpr 在编译的时候舍弃代码，以匹配模板参数
    // 用于类型特性的_v变量模板——无需编写std::trait_name<T>::value
    if constexpr (std::is_integral_v<T>)
        std::cout << "num: " << x << '\n ';
    else if constexpr (std::is_floating_point_v<T>) {
        const auto frac = x - static_cast<long>(x);
        std::cout << "flt: " << x << ", frac " << frac << std::endl;
    }
    else if constexpr(std::is_pointer_v<T>) {
        std::cout << "ptr, ";
        linePrinter(*x);
    }
    else
        std::cout << x << std::endl;
}

// 可变模板参数，可以接受任意数量、任意类型的参数
template <typename... Args> void printWithInfo(Args... args) {
    // c++ 17 折叠表达式，等价于对于每个args调用linePrinter
    (linePrinter(args),...); // 逗号运算符上的折叠表达式
}

int main () {
    int i = 10;
    float f = 2.56f;
    printWithInfo(&i, &f, 30);
}

// g++ -std=c++17 demo_print.cpp -o demo_print
// ./demo_print
