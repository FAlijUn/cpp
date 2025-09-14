#include <iostream>

template <auto value>
void f() {
    std::cout << value << '\n';
}

// C++14 style
// template <typename Type, Type value>
// constexpr Type TConstant = value;
// constexpr auto const MySuperConst = TConstant<int, 100>;

// C++17 style
template <auto value>
constexpr auto TConstant = value;
constexpr auto const MySuperConst = TConstant<100>;

// 异构编译列表
template <auto... vs>
struct HeterogenousValueList {};
using MyList = HeterogenousValueList<'a', 100, 'b'>;

int main() {
    f<42>();
    f<'a'>();
    return 0;
}