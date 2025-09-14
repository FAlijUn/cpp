#include <iostream>

// template <typename T>
// T simpleTypeInfoTagImpl(T t, std::true_type) {
//     std::cout << "foo<integral T> " << t << '\n';
//     return t;
// }

// template <typename T>
// T simpleTypeInfoTagImpl(T t, std::false_type) {
//     std::cout << "not integral \n";
//     return t;
// }

// template <typename T>
// T simpleTypeInfoTag(T t) {
//     return simpleTypeInfoTagImpl(t, std::is_integral<T>{});
// }


template <typename T>
T simpleTypeInfo(T t) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "foo<integral T> " << t << '\n';
    } else {
        std::cout << "not integral \n";
    }
    return t;
}


int main() {
    simpleTypeInfo(42);
    simpleTypeInfo(3.14);
    return 0;
}
// g++ -std=c++17 -o demo_template_multi_stage demo_template_multi_stage.cpp
// ./demo_template_multi_stage


