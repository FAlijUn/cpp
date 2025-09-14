namespace [[deprecated("use BetterUtils")]] GoodUtils {
    void DoStuff() { }
}

namespace BetterUtils {
    void DoStuff() { }
}
// 使用:
GoodUtils::DoStuff();

//warning: 'GoodUtils' is deprecated: use BetterUtils [-Wdeprecated-declarations]

enum class ColorModes {
    RGB [[deprecated("use RGB8")]],
    RGBA [[deprecated("use RGBA8")]],
    RGB8,
    RGBA8
};
// 使用:
auto colMode = ColorModes::RGBA;

warning: 'RGBA' is deprecated: use RGBA8 [-Wdeprecated-declarations]
    