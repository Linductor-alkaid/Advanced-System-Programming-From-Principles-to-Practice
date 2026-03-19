#include <iostream>

class Base {
public:
    virtual void func(int x) { std::cout << "Base::func int\n"; }
    void func(double x) { std::cout << "Base::func double\n"; }
};

class Derived : public Base {
public:
    // 使用 using 引入基类所有重载
    using Base::func;

    void func(int x) override { std::cout << "Derived::func int\n"; }
};

int main() {
    Derived d;
    d.func(1);     // Derived::func int
    d.func(1.0);   // Base::func double (因为有 using)

    return 0;
}
