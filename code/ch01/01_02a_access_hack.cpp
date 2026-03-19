#include <iostream>

class Secret {
private:
    int privateValue = 42;  // 私有成员
};

void hack() {
    Secret obj;

    // 方法1：通过指针直接访问（危险！）
    int* ptr = (int*)&obj;
    std::cout << "Private value: " << *ptr << std::endl;  // 输出: 42

    // 方法2：通过内存偏移访问
    char* raw = (char*)&obj;
    int* valuePtr = (int*)(raw + 0);  // 假设privateValue在偏移0处
    std::cout << "Private value: " << *valuePtr << std::endl;  // 输出: 42
}

int main() {
    hack();
    return 0;
}
