#include <iostream>
#include <cstddef>

class Base1 {
public:
    int b1Data_;
    virtual void func1() { std::cout << "Base1::func1\n"; }
    virtual void funcB1() { std::cout << "Base1::funcB1\n"; }
    Base1(int data) : b1Data_(data) {}
};

class Base2 {
public:
    int b2Data_;
    virtual void func2() { std::cout << "Base2::func2\n"; }
    virtual void funcB2() { std::cout << "Base2::funcB2\n"; }
    Base2(int data) : b2Data_(data) {}
};

class Derived : public Base1, public Base2 {
public:
    int dData_;

    Derived(int b1, int b2, int d)
        : Base1(b1), Base2(b2), dData_(d) {}

    void func1() override { std::cout << "Derived::func1\n"; }
    void func2() override { std::cout << "Derived::func2\n"; }
    virtual void funcD() { std::cout << "Derived::funcD\n"; }
};

void inspectMultiInheritance() {
    Derived d(1, 2, 3);

    std::cout << "=== Multiple Inheritance Memory Layout ===\n";
    std::cout << "sizeof(Derived) = " << sizeof(Derived) << " bytes\n\n";

    // 作为Base1*访问
    Base1* b1 = &d;
    std::cout << "As Base1*:\n";
    std::cout << "  Address: " << b1 << "\n";
    std::cout << "  vptr content: " << *(const void**)b1 << "\n";
    b1->func1();  // Derived::func1

    // 作为Base2*访问（地址会调整！）
    Base2* b2 = &d;
    std::cout << "\nAs Base2*:\n";
    std::cout << "  Address: " << b2 << " (offset from Derived: "
              << (char*)b2 - (char*)&d << " bytes)\n";
    std::cout << "  vptr content: " << *(const void**)b2 << "\n";
    b2->func2();  // Derived::func2

    std::cout << "\nExplanation:\n";
    std::cout << "  - Derived has TWO vptrs (one for each base)\n";
    std::cout << "  - Converting to Base2* adjusts the pointer\n";
    std::cout << "  - Each base class has its own vtable\n";
}

int main() {
    inspectMultiInheritance();
    return 0;
}
