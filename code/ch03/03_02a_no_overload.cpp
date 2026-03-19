#include <iostream>
#include <string>

// 代码重复：为每种类型编写单独的函数
void printInt(int value) {
    std::cout << "Integer: " << value << "\n";
}

void printDouble(double value) {
    std::cout << "Double: " << value << "\n";
}

void printString(const std::string& value) {
    std::cout << "String: " << value << "\n";
}

// 代码重复：比较函数
int maxInt(int a, int b) {
    return (a > b) ? a : b;
}

double maxDouble(double a, double b) {
    return (a > b) ? a : b;
}

int main() {
    printInt(42);
    printDouble(3.14);
    printString("Hello");

    std::cout << "Max int: " << maxInt(10, 20) << "\n";
    std::cout << "Max double: " << maxDouble(1.5, 2.5) << "\n";

    return 0;
}
