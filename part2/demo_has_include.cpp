// 在C++17中，你可以使用has_include预处理常量表达式来检查某个给定的头文件是否存在：
// 我们根据has_include条件声明了has_charconv。如果头文件不存在，我们需要为ConvertToInt提供一个替代实现
#include <charconv>
#include <iostream>
#include <optional>
#include <string>
#if defined has_include
#    if has_include(<charconv>)
#        define has_charconv 1
#        include <charconv>
#    endif
#endif

std::optional<int> ConvertToInt(const std::string& str) {
    int value { };
#ifdef has_charconv
    const auto last = str.data() + str.size();
    const auto res = std::from_chars(str.data(), last, value);
    if (res.ec == std::errc{} && res.ptr == last)
        return value;
#else
    // alternative implementation...
#endif

    return std::nullopt;
}
