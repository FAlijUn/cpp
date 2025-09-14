// 自C++11引入移动语义（move semantics）以来，传递字符串变得快多了。
// 然而，你可能会遇到很多临时字符串副本的问题。
// 在C++17中，出现了一种新类型string_view。
// 它允许你创建一个指向连续字符序列的常量、非拥有型视图。
// 你可以操作这个视图并传递它，而无需复制被引用的数据。
// 不过，这个特性也有一些代价：你需要注意避免出现“悬空”视图，而且通常这样的视图可能不是以空字符结尾的。
#include <iostream>
#include <string>
#include <string_view>

std::string StartFromWordStr(const std::string& strArg, const std::string& word) {
    return strArg.substr(strArg.find(word)); // substr函数创建一个新字符
}

std::string_view StartFromWord(std::string_view str, std::string_view word) {
    return str.substr(str.find(word)); 
}

int main()
{
    std::string str {"Hello Amazing Programming Environment" }; // 创建一个字符串副本
    auto subStr = StartFromWordStr(str, "Programming Environment"); // 传递的是 const char* 创建一个字符串副本

    std::cout << subStr << '\n';

    auto subView = StartFromWord(str, "Programming Environment");
    std::cout << subView << '\n';
}
// string_view会被拷贝——但由于它只是一个指针和一个长度，所以比拷贝整个字符串高效得多
// 在任何情况下，都要记住它只是一个非拥有型视图，所以如果原始对象不存在了，这个视图就会变得毫无意义，你可能会遇到问题
// string_view可能不包含空字符终止符，所以你的代码也必须支持这一点。例如，将string_view传递给一个接受以空字符结尾的字符串的函数
