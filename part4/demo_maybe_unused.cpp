#include <iostream>

static void impl1() { std::cout << "impl1" << std::endl; } // 当函数未被调用时，编译器可能会发出警告
[[maybe_unused]] static void impl2() { std::cout << "impl2" << std::endl; } // 警告被抑制

void foo() {
    int x = 42; // 如果之后x未被使用，编译器可能会发出警告
    [[maybe_unused]] int y = 42; // 对y的警告被抑制
}
