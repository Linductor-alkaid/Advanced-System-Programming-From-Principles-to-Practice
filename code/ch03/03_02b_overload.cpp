#include <iostream>
#include <string>

// 函数重载：统一接口名
void print(int value) {
    std::cout << "Integer: " << value << "\n";
}

void print(double value) {
    std::cout << "Double: " << value << "\n";
}

void print(const std::string& value) {
    std::cout << "String: " << value << "\n";
}

// 参数数量不同的重载
void log(const std::string& msg) {
    std::cout << "[LOG] " << msg << "\n";
}

void log(const std::string& level, const std::string& msg) {
    std::cout << "[" << level << "] " << msg << "\n";
}

void log(const std::string& level, const std::string& msg, int code) {
    std::cout << "[" << level << "] " << msg << " (code: " << code << ")\n";
}

int main() {
    // 编译器根据参数类型选择正确的函数
    print(42);           // 调用 print(int)
    print(3.14);         // 调用 print(double)
    print("Hello");      // 调用 print(const char*),可能隐式转换

    print(std::string("World"));  // 调用 print(const std::string&)

    // 不同参数数量的重载
    log("Info");
    log("Warning", "Low memory");
    log("Error", "File not found", 404);

    return 0;
}
