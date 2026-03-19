#include <iostream>

class Base1 {
public:
    int x = 1;
    virtual void f1() {}
};

class Base2 {
public:
    int y = 2;
    virtual void f2() {}
};

class Derived : public Base1, public Base2 {
public:
    int z = 3;
    void f1() override {}
    void f2() override {}
};

int main() {
    Derived d;
    Base2* b2 = &d;

    // ❌ 危险：C风格转换可能不正确调整指针
    Derived* bad = (Derived*)b2;
    std::cout << "C-style cast result: " << bad << "\n";

    // ✅ 正确：使用static_cast
    Derived* good = static_cast<Derived*>(b2);
    std::cout << "static_cast result: " << good << "\n";

    // good指向正确的对象地址，bad可能指向错误的位置

    return 0;
}
