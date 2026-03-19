#include <iostream>
#include <memory>

class Base {
public:
    int baseResource_;

    Base() : baseResource_(0) {
        std::cout << "Base::Base() - 构造基类部分\n";
    }

    virtual ~Base() {
        std::cout << "Base::~Base() - 析构基类部分, 释放 baseResource_\n";
    }
};

class Middle : public Base {
public:
    int middleResource_;

    Middle() : middleResource_(0) {
        std::cout << "Middle::Middle() - 构造中间类部分\n";
    }

    virtual ~Middle() {
        std::cout << "Middle::~Middle() - 析构中间类部分, 释放 middleResource_\n";
    }
};

class Derived : public Middle {
public:
    int derivedResource_;

    Derived() : derivedResource_(0) {
        std::cout << "Derived::Derived() - 构造派生类部分\n";
    }

    ~Derived() override {
        std::cout << "Derived::~Derived() - 析构派生类部分, 释放 derivedResource_\n";
    }
};

void demonstrateOrder() {
    std::cout << "=== 构造顺序 ===\n";
    Derived* d = new Derived();

    std::cout << "\n=== 析构顺序 ===\n";
    delete d;
}

int main() {
    demonstrateOrder();
    return 0;
}
