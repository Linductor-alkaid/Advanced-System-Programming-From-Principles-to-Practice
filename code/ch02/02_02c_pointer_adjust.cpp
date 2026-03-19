#include <iostream>
#include <cstdint>

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
    std::cout << "Derived object address: " << &d << "\n";

    Base1* b1 = &d;
    Base2* b2 = &d;

    std::cout << "\nPointer conversion:\n";
    std::cout << "  Derived* -> " << &d << "\n";
    std::cout << "  Base1*   -> " << b1 << " (no adjustment)\n";
    std::cout << "  Base2*   -> " << b2 << " (adjusted by +"
              << (char*)b2 - (char*)&d << " bytes)\n";

    // 转换回去
    Derived* d1 = static_cast<Derived*>(b1);
    Derived* d2 = static_cast<Derived*>(b2);

    std::cout << "\nConvert back to Derived*:\n";
    std::cout << "  from Base1* -> " << d1 << " (no adjustment)\n";
    std::cout << "  from Base2* -> " << d2 << " (adjusted by "
              << (char*)d2 - (char*)b2 << " bytes)\n";

    // 验证最终地址相同
    std::cout << "\nVerification: d1 == d2? " << (d1 == d2 ? "yes" : "no") << "\n";
    std::cout << "  d1 == &d? " << (d1 == &d ? "yes" : "no") << "\n";
    std::cout << "  d2 == &d? " << (d2 == &d ? "yes" : "no") << "\n";

    return 0;
}
