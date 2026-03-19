#include <iostream>
#include <string>
#include <vector>

// 函数模板：类型参数化
template<typename T>
void print(const T& value) {
    std::cout << "Value: " << value << "\n";
}

// 模板实现比较函数
template<typename T>
T maximum(const T& a, const T& b) {
    return (a > b) ? a : b;
}

// 多个类型参数的模板
template<typename T, typename U>
auto add(const T& a, const U& b) -> decltype(a + b) {
    return a + b;
}

// 非类型模板参数
template<int N>
void repeat(const std::string& msg) {
    for (int i = 0; i < N; ++i) {
        std::cout << msg << "\n";
    }
}

int main() {
    // 编译器自动推导类型并生成对应函数
    print(42);           // 实例化 print<int>
    print(3.14);         // 实例化 print<double>
    print(std::string("Hello"));  // 实例化 print<std::string>

    std::cout << "Max int: " << maximum(10, 20) << "\n";
    std::cout << "Max double: " << maximum(1.5, 2.5) << "\n";

    // 不同类型的加法
    std::cout << "Add: " << add(100, 1.5) << "\n";  // int + double
    std::cout << "Add: " << add(2.5f, 3) << "\n";   // float + int

    // 非类型模板参数
    repeat<3>("Hello!");  // 编译期确定循环次数

    return 0;
}
