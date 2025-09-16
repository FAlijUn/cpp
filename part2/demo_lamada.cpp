// 常量表达式（constexpr）lambda表达式
// - 不能是虚函数
// - 返回值类型必须是字面值类型
// - 参数必须是字面值类型
// - 它们的函数体不能包含：asm定义、goto语句、try块，或者非字面量类型、具有静态或线程存储期的变量
int main () {
    constexpr auto SquareLambda = [](int n) { return n*n; };
    static_assert(SquareLambda(3) == 9, "");
}
