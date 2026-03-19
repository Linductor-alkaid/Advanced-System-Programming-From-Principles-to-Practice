#include <iostream>

class Base {
public:
    virtual void criticalFunction() {
        std::cout << "Base::criticalFunction - 核心逻辑\n";
    }

    virtual void flexibleFunction() {
        std::cout << "Base::flexibleFunction - 可覆盖\n";
    }

    virtual ~Base() = default;
};

class Middle : public Base {
public:
    void criticalFunction() override {  // 覆盖基类
        std::cout << "Middle::criticalFunction\n";
    }

    // 标记为 final：派生类不能进一步覆盖
    void flexibleFunction() override final {
        std::cout << "Middle::flexibleFunction - 不允许再覆盖\n";
    }
};

class Derived : public Middle {
public:
    // 错误：不能覆盖 final 函数
    // void flexibleFunction() override {
    //     std::cout << "Derived::flexibleFunction\n";
    // }

    // 可以覆盖非 final 函数
    void criticalFunction() override {
        std::cout << "Derived::criticalFunction\n";
        Middle::criticalFunction();  // 调用中间层版本
    }
};

int main() {
    Derived d;
    d.criticalFunction();
    d.flexibleFunction();  // 调用 Middle::flexibleFunction

    return 0;
}
