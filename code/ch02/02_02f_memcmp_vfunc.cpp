#include <iostream>
#include <cstring>

class Base1 {
public:
    int a = 1;
    virtual void f() {}
};

class Base2 {
public:
    int b = 2;
    virtual void g() {}
};

class Derived : public Base1, public Base2 {
public:
    int c = 3;
    void f() override {}
    void g() override {}
};

int main() {
    Derived d1, d2;
    d1.c = 100;
    d2.c = 100;

    // ❌ 危险：使用memcmp比较含虚函数的对象
    // vptr的值可能在运行时不同，即使对象"相等"
    if (memcmp(&d1, &d2, sizeof(Derived)) == 0) {
        std::cout << "Equal\n";
    } else {
        std::cout << "Not equal (vptr may differ)\n";
    }

    // ✅ 正确：重载operator==进行比较
    return 0;
}
