#include <iostream>

class A {
public:
    A(int x) : val(x) {
        std::cout << "A constructor: " << val << "\n";
    }
    int val;
};

class B : virtual public A {
public:
    B() : A(1) {  // 虚基类的初始化由最远派生类控制
        std::cout << "B constructor\n";
    }
};

class C : virtual public A {
public:
    C() : A(2) {  // 这里的初始化会被忽略
        std::cout << "C constructor\n";
    }
};

class D : public B, public C {
public:
    // 最远派生类负责初始化虚基类
    D() : A(100) {
        std::cout << "D constructor\n";
    }
};

int main() {
    D d;
    std::cout << "A::val = " << d.val << "\n";
    return 0;
}
