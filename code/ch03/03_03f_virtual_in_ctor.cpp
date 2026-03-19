#include <iostream>
#include <string>

class Base {
public:
    Base() {
        init();  // 调用虚函数
    }
    virtual void init() { std::cout << "Base::init\n"; }
    virtual ~Base() { cleanup(); }
    virtual void cleanup() { std::cout << "Base::cleanup\n"; }
};

class Derived : public Base {
    std::string data_;
public:
    Derived() : data_("important") {}
    void init() override {
        std::cout << "Derived::init, data=" << data_ << "\n";
    }
    void cleanup() override {
        std::cout << "Derived::cleanup\n";
    }
};

int main() {
    Derived d;
    // 输出:
    // Base::init        (不是 Derived::init!)
    // Base::cleanup     (不是 Derived::cleanup!)
}
