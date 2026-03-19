#include <iostream>

class Base {
public:
    virtual void func() {}
    int x;
};

class Derived : public Base {
public:
    int y;
};

int main() {
    // ❌ 错误假设：sizeof(Derived) == sizeof(Base) + sizeof(y)
    std::cout << "sizeof(Base) = " << sizeof(Base) << "\n";
    std::cout << "sizeof(Derived) = " << sizeof(Derived) << "\n";

    // ✅ 实际情况（64位系统）：
    // sizeof(Base) = 16 (vptr 8字节 + int x 4字节 + padding 4字节)
    // sizeof(Derived) = 24 (vptr 8字节 + int x 4字节 + int y 4字节 + padding 8字节)
    // 注意：Derived的padding是因为y之后要对齐到8字节边界

    return 0;
}
