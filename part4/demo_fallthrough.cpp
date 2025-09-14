#include <iostream>
int main()
{
    switch (c) {
    case 'a':
        std::cout << "a\n"; 
    case 'b':
        std::cout << "b\n";
        [[fallthrough]]; // 警告被抑制，穿透是允许的
    case 'c':
        std::cout << "c\n";
        break;
    default:
        std::cout << "default\n";
    }

}