#include <iostream>

class Base {
public:
    virtual void func() const { std::cout << "Base\n"; }
};

class Derived : public Base {
public:
    void func() const override { std::cout << "Derived\n"; }
    void extra() { std::cout << "Extra\n"; }
};

// 按值传递导致对象切片
void processByValue(Base obj) {  // 对象被切片为 Base
    obj.func();  // 输出: Base（不是 Derived！）
}

// 正确：按引用传递
void processByRef(const Base& obj) {
    obj.func();  // 输出: Derived
}

int main() {
    Derived d;
    processByValue(d);   // 输出: Base（多态失效！）
    processByRef(d);     // 输出: Derived

    return 0;
}
