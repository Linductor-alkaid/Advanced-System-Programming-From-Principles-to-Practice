#include <iostream>

class Base {
public:
    Base() {
        std::cout << "Base constructor\n";
    }
    ~Base() {
        std::cout << "Base destructor\n";
    }
};

class Derived : public Base {
public:
    Derived() {
        std::cout << "Derived constructor\n";
    }
    ~Derived() {
        std::cout << "Derived destructor\n";
    }
};

int main() {
    {  // 作用域
        Derived d;
    }  // d在这里销毁
}
