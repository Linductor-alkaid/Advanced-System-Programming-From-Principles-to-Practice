#include <iostream>
#include <memory>

class Base {
public:
    // 危险：没有虚析构函数
    ~Base() { std::cout << "Base destructor\n"; }

    virtual void func() { std::cout << "Base::func\n"; }
};

class Derived : public Base {
    int* data_;

public:
    Derived() : data_(new int(42)) {
        std::cout << "Derived constructor, data=" << *data_ << "\n";
    }

    ~Derived() {
        std::cout << "Derived destructor, deleting data\n";
        delete data_;
    }

    void func() override {
        std::cout << "Derived::func, data=" << *data_ << "\n";
    }
};

int main() {
    std::cout << "=== Case 1: 直接删除派生类指针 ===\n";
    {
        Derived* d = new Derived();
        delete d;  // 正确：调用Derived和Base析构函数
    }

    std::cout << "\n=== Case 2: 删除基类指针（危险！） ===\n";
    {
        Base* b = new Derived();
        delete b;  // 危险！只调用Base析构函数，内存泄漏！
        // 输出只显示 "Base destructor"，没有 "Derived destructor"
    }

    std::cout << "\n=== Case 3: 使用智能指针（仍需虚析构函数） ===\n";
    {
        std::unique_ptr<Base> b = std::make_unique<Derived>();
        // 仍然有问题！unique_ptr<Base>删除时仍只调用Base析构函数
    }

    return 0;
}
