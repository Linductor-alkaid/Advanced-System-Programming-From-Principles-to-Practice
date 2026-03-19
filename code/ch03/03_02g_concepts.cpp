// Requires C++20
#include <iostream>
#include <concepts>

// C++20 概念
template<std::integral T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << "add(10, 20) = " << add(10, 20) << "\n";
    // add(1.5, 2.5);   // 编译错误：double不是整数类型
    return 0;
}
