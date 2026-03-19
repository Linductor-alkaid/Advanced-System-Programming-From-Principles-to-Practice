#include <iostream>

class Base {
public:
    int data_;
    virtual void func() { std::cout << "Base::func, data=" << data_ << "\n"; }
    Base(int data) : data_(data) {}
};

class Derived1 : virtual public Base {
public:
    int d1Data_;
    Derived1(int base, int d1) : Base(base), d1Data_(d1) {}
    void func() override { std::cout << "Derived1::func\n"; }
};

class Derived2 : virtual public Base {
public:
    int d2Data_;
    Derived2(int base, int d2) : Base(base), d2Data_(d2) {}
    void func() override { std::cout << "Derived2::func\n"; }
};

class Diamond : public Derived1, public Derived2 {
public:
    Diamond(int base, int d1, int d2)
        : Base(base), Derived1(base, d1), Derived2(base, d2) {}
    void func() override { std::cout << "Diamond::func\n"; }
};

void inspectVirtualInheritance() {
    std::cout << "=== Virtual Inheritance Memory Layout ===\n\n";

    Base b(1);
    Derived1 d1(10, 11);
    Derived2 d2(20, 21);
    Diamond dm(100, 101, 102);

    std::cout << "sizeof(Base) = " << sizeof(Base) << "\n";
    std::cout << "sizeof(Derived1) = " << sizeof(Derived1) << "\n";
    std::cout << "sizeof(Derived2) = " << sizeof(Derived2) << "\n";
    std::cout << "sizeof(Diamond) = " << sizeof(Diamond) << "\n\n";

    std::cout << "Addresses:\n";
    std::cout << "  Base b:          " << &b << "\n";
    std::cout << "  Derived1 d1:     " << &d1 << "\n";
    std::cout << "  Derived2 d2:     " << &d2 << "\n";
    std::cout << "  Diamond dm:      " << &dm << "\n";

    // 虚继承下，Base子对象只有一个
    std::cout << "\nKey points:\n";
    std::cout << "  - Virtual inheritance adds a vptr to each class\n";
    std::cout << "  - Diamond contains only ONE Base subobject\n";
    std::cout << "  - Access to Base members goes through the vtable\n";
}

int main() {
    inspectVirtualInheritance();
    return 0;
}
