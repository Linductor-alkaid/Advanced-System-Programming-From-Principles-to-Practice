#include <iostream>
#include <type_traits>
#include <string>

// SFINAE：Substitution Failure Is Not An Error
template<typename T>
typename std::enable_if<std::is_integral<T>::value>::type
process(T value) {
    std::cout << "Processing integer: " << value << "\n";
}

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value>::type
process(T value) {
    std::cout << "Processing floating point: " << value << "\n";
}

// C++17 更简洁的写法
template<typename T>
std::enable_if_t<std::is_same_v<T, std::string>>
process(const T& value) {
    std::cout << "Processing string: " << value << "\n";
}

int main() {
    process(42);        // 调用整数版本
    process(3.14);      // 调用浮点版本
    process(std::string("Hello"));  // 调用字符串版本

    return 0;
}
