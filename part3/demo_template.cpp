// 类的模板参数的推导
#include <iostream>
#include <string>
using namespace std::string_literals;

int main()
{
    // 要创建一个std::pair对象，通常这样写会更方便
    auto myPair = std::make_pair(42, "hello world"s);
    // 不需要指定模板参数，编译器会自动推导出模板参数类型
    auto myPair_1 = std::make_pair<int, std::string>(42, "hello world");

    // 类模板参数推导 Class Template Argument Deduction (CTAD)
    // CATD在拷贝初始化和通过 new 分配内存时也同样适用
    auto otherPair = std::pair(42, "hello world"s);
    auto ptr = new std::pair(42, "hello world"s);

    // CATD 可以大幅简化复杂的构造
    // 锁保护
    std::shared_timed_mutex mtx;
    std::lock_guard lock(mtx); // std::lock_guard<std::shared_timed_mutex> lock(mtx);
    // 数组
    std::array arr{1, 2, 3, 4, 5}; // std::array<int, 5> arr{1, 2, 3, 4, 5};

}
// g++ -std=c++17 demo_template.cpp -o demo_template
