#include <iostream>

class Base {
public:
    virtual void func() { std::cout << "Base\n"; }
};

class Derived : public Base {
public:
    void func() override { std::cout << "Derived\n"; }
    void extra() { std::cout << "Extra\n"; }
};

// 按值传递导致对象切片
void processByValue(Base obj) {
    obj.func();  // 输出: Base（派生类部分被切掉）
}

// 按引用传递
void processByRef(Base& obj) {
    obj.func();  // 输出: Derived
}

int main() {
    Derived d;
    processByValue(d);   // 输出: Base
    processByRef(d);     // 输出: Derived
    return 0;
}
