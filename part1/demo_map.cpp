#include <iostream>
#include <map>

int main() {
    std::map<std::string, int> mapUsersAge { { "Alex", 45 }, { "John", 25 } };
    // 类模板的模板参数推导（Template Argument Deduction for Class Templates）
    // mapCopy的类型从mapUsersAge的类型推导得出。无需声明std::map<std::string, int> mapCopy{...}
    std::map mapCopy{mapUsersAge};

    // 映射的新插入成员函数——insert_or_assign
    // 将insert_or_assign返回的pair解包为不同的变量名
    if (auto [iter, wasAdded] = mapCopy.insert_or_assign("John", 26);!wasAdded)
        std::cout << iter->first << " reassigned..." <<std::endl;

    // 基于范围的for循环中的结构化绑定——我们可以使用key和value进行迭代，而不是pair.first和pair.second
    for (const auto& [key, value] : mapCopy)
        std::cout << key << ", " << value << std::endl;
}
// g++ -std=c++17 demo_map.cpp -o demo_map
// ./demo_map