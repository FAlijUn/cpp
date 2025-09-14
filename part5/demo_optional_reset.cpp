#include <optional> 
#include <iostream> 
#include <string>

// 如果你已经有一个std::optional对象，
// 可以通过emplace、reset、swap、assign等操作快速修改其中包含的值


class UserName {
public:
    explicit UserName(std::string str) : mName(std::move(str)) {
        std::cout << "UserName::UserName('" << mName << " ')\n ";
    }
    ~UserName() {
        std::cout << "UserName::~UserName('" << mName << " ')\n ";
    }
private:
    std::string mName; 
};

int main() {
    std::optional<UserName> oEmpty;
    // emplace:
    oEmpty.emplace("Steve");
    // 调用~Steve并创建新的Mark:
    oEmpty.emplace("Mark");
    // 重置，使其再次为空
    oEmpty.reset(); // 调用~Mark 
    // 等同于:
    //oEmpty = std::nullopt;
    // 赋值一个新值:
    oEmpty.emplace("Fred");
    oEmpty = UserName("Joe");
    // 每次对象发生改变时，当前存储的UserName的析构函数都会被调用
}
