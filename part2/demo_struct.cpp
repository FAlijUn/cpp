// 结构化绑定
#include <iostream>
#include <set>
#include <tuple>

std::pair<int, bool> InsertElement(int el) { 
    return {el, true};
}

// 自定义结构化绑定
class UserEntry {
public:
    void Load() {}
    std::string GetName() const { return name; }
    unsigned GetAge() const { return age; }
private:
    std::string name;
    unsigned age { 0 };
    size_t cacheEntry { 0 }; // 不公开
};

template <size_t I> auto get(const UserEntry& u) {
    if constexpr (I == 0) return u.GetName();
    else if constexpr (I == 1) return u.GetAge();
}

namespace std {
    template <> struct tuple_size<UserEntry> : integral_constant<size_t, 2> {};
    template <> struct tuple_element<0,UserEntry> { using type = std::string; };
    template <> struct tuple_element<1,UserEntry> { using type = unsigned; };
}

int main(){
    int index{10};
    bool flag{false};
    auto [idx, fl] = InsertElement(5);
    std::cout << "index: " << idx << ", flag: " << fl << std::endl;
    
    std::cout << "==========================" << std::endl;

    std::set<int> Myset;
    auto [iter, success] = Myset.insert(10);
    if (success) {
        std::cout << "Element " << *iter << " inserted successfully." << std::endl;
    } 

    std::cout << "==========================" << std::endl;

    // 修饰符号可以用于结构化绑定
    const auto [i, j] = std::make_pair(1, 2);
    // 引用修饰符
    auto p = std::make_pair(i, j);
    auto& [x, y] = p; // 正确
    auto&& [m, n] = p; // 正确
 
    std::cout << "==========================" << std::endl;
    UserEntry user;
    user.Load();
    auto [name, age] = user;
    std::cout << "name: " << name << ", age: " << age << std::endl;

    return 0;
}

// g++ -std=c++17 demo_struct.cpp -o demo_struct
// ./demo_struct