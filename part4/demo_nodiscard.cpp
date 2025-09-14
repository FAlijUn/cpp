#include <string_view>

[[nodiscard]] int Compute();

void Test() {
    Compute(); // 警告！带有nodiscard标注的函数返回值被丢弃
}

// 如果你忘记将结果赋值给变量，编译器应该发出警告。

// 该标注还可以应用于类型。一个用例可能是错误码类型：

enum class [[nodiscard]] ErrorCode {
    OK,
    Fatal,
    System,
    FileIssue
};

ErrorCode OpenFile(std::string_view fileName);
ErrorCode SendEmail(std::string_view sendto,
                    std::string_view text);
ErrorCode SystemCall(std::string_view text);
