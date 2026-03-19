#include <iostream>
#include <string>

class Base {
public:
    Base() {
        init();  // 调用虚函数
    }

    virtual void init() {
        std::cout << "Base::init\n";
    }

    virtual ~Base() = default;
};

class Derived : public Base {
    std::string data_;
public:
    Derived() : data_("important") {
        // 此时Base构造函数已经执行完毕
    }

    void init() override {
        std::cout << "Derived::init, data=" << data_ << "\n";
    }
};

int main() {
    Derived d;
    // 输出: Base::init
    // 不会输出 "Derived::init"！
}
