#include <iostream>

// 编译期阶乘计算
template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};

// 模板特例化作为递归终止
template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

int main() {
    // 编译期计算，无需运行时开销
    constexpr int result = Factorial<5>::value;  // = 120
    std::cout << "Factorial<5> = " << result << "\n";
    return 0;
}
