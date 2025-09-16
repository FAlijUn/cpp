#include <iostream>

int main(){
    const std::string myString = "My Hello World Wow";
    const auto pos = myString.find("Hello");
    if (pos != std::string::npos)
        std::cout << pos << " Hello\n";
    const auto pos2 = myString.find("World");
    if (pos2 != std::string::npos)
        std::cout << pos2 << " World\n";
    
    std::cout << "==========================" << std::endl;

    if (const auto pos = myString.find("Hello"); pos != std::string::npos)
        std::cout << pos << " Hello\n";
    if (const auto pos = myString.find("World"); pos != std::string::npos)
        std::cout << pos << " World\n";

    std::cout << "==========================" << std::endl;
    // pos 作用域仅在 if 内
    if (const auto pos = myString.find("World"); pos != std::string::npos)
        std::cout << pos << " World\n";
    else
        std::cout << pos << " not found!!\n";


    return 0;
}