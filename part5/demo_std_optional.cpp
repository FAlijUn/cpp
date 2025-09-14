// 标记一个类型不包含任何值
// 构建一个包装器，为其他类型添加一个布尔标志。这样的包装器可以快速判断对象的状态。简而言之，std::optional就是这样工作的
// 使用场景
// 1. 希望表示一个可空类型
// 例如，用户的中间名是可选的。你可能认为空字符串在这里可行，但了解用户是否输入了内容可能很重要。std::optional<std::string>可以提供更多信息
// 2. 返回某些计算（处理）的结果，当计算未能产生值且并非错误时。
// 例如，在字典中查找元素：如果某个键下没有元素，这不是错误，但我们需要处理这种情况。
// 3. 实现资源的延迟加载。
// 例如，如果资源类型的构造开销很大，或者没有默认构造函数，你可以将其定义为std::optional<Resource>。以这种形式，你可以在系统中传递它，然后在应用程序首次访问时对其进行初始化（加载资源）。
// 4. 向函数传递可选参数
// 建议在存在唯一一个各方都清楚的没有T类型值的原因，并且没有值与拥有任何常规T类型值一样自然的情况下，使用optional<T>。

#include <optional>

struct Point {
    Point(int a, int b) : x(a), y(b) {}
    int x;
    int y;
};

template < class... Args >
constexpr explicit optional( std::in_place_t, Args&&... args );

// 或者初始化列表:
template < class U, class... Args >
constexpr explicit optional( std::in_place_t,
                             std::initializer_list<U> ilist,
                             Args&&... args );

std::optional<std::string> CreateString() {
    std::string str {"Hello Super Awesome Long String"};
    return {str}; // 这会导致拷贝
    // return str;   // 这会进行移动操作
}


int main()
{
    // 空初始化
    std::optional<int> oEmpty; // 默认构造函数，表示没有值
    std::optional<float> oFloat = std::nullopt; // 显式初始化为空

    // 直接初始化
    std::optional<int> oInt1(42); // 直接初始化为42
    std::optional oIntDeduce(42); // 使用类模板参数推导，C++17起支持

    // make_optional
    auto oDouble = std::make_optional(3.14); // 使用make_optional函数创建
    auto oComplex = std::make_optional<std::complex<double>>(1.0, 2.0); // 也可以指定类型

    // in_place 原地构造，直接在内部存储空间中构造一个对象，而不是先构造一个临时对象再拷贝或移动进去
    std::optional<std::string> oString(std::in_place, "Hello, std::optional!");

    // 拷贝
    auto oCopy = oString; // 拷贝构造

    // 就地构造
    std::optional<std::string> ostr{"Hello World"};
    std::optional<int> oi{10};
    // 也可以不编写构造函数
    std::optional<std::string> ostr{std::string{"Hello World"}};
    std::optional<int> oi{int {10}};
    
    // 不可复制/不可移动类型：正如你在上一节的示例中看到的，
    // 如果你使用一个临时对象来初始化std::optional中包含的值，
    // 那么编译器将不得不使用移动或复制构造函数。但如果你的类型不允许这样做呢？
    // 例如，std::mutex是不可移动也不可复制的。
    // 在这种情况下，std::in_place是处理这类类型的唯一方法


    // 有多个参数的构造函数：另一个用例是当你的类型在构造函数中有更多参数时。
    // 默认情况下，optional可以处理单个参数（右值引用），并有效地将其传递给被包装的类型。
    // 但如果你想初始化Point(x, y)呢？你总是可以创建一个临时副本，然后在构造时传递它：
    std::optional<Point> opt{Point{0, 0}}; // 创建了临时对象!

    // 避免了创建临时对象。对于容器或较大的对象来说，临时对象的效率不如就地构造。
    std::optional<Point> opt{std::in_place_t, 0, 0};


    std::cout << "==============================" << std::endl;

    auto opt = std::make_optional<UserName>();
    auto opt = std::make_optional<Point>(0, 0);
    // 等同于
    std::optional<UserName> opt{std::in_place};
    std::optional<Point> opt{std::in_place_t, 0, 0};
    // std::make_optional实现了等同于return std::optional<T>(std::in_place, std::forward<Args>(args)...);的就地构造

    std::cout << "==============================" << std::endl;

    // 通过operator*
    std::optional<int> oint = 10;
    std::cout<< "oint " << *oint << '\n ';
    // 通过value()
    std::optional<std::string> ostr("hello");
    try {
        std::cout << "ostr " << ostr.value() << '\n ';
    }
    catch (const std::bad_optional_access& e) {
        std::cout << e.what() << '\n ';
    }
    // 通过value_or()
    std::optional<double> odouble; // 空值
    std::cout<< "odouble " << odouble.value_or(10.0) << '\n ';

    // 计算字符串的函数：
    std::optional<std::string> maybe_create_hello();
    // ...
    if (auto ostr = maybe_create_hello(); ostr)
        std::cout << "ostr " << *ostr << '\n ';
    else
        std::cout << "ostr is null\n ";


}

