#include <iostream>
#include <memory>
#include <cstring>

// 危险：基类析构函数不是虚函数
class Base {
public:
    int* baseData_;

    Base() : baseData_(new int(100)) {
        std::cout << "Base constructor, allocating baseData_\n";
    }

    ~Base() {  // 不是虚函数！
        std::cout << "Base destructor, freeing baseData_\n";
        delete baseData_;
    }

    virtual void func() {
        std::cout << "Base::func\n";
    }
};

class Derived : public Base {
public:
    char* derivedData_;

    Derived() : Base(), derivedData_(new char[1024]) {
        std::cout << "Derived constructor, allocating derivedData_\n";
        std::memcpy(derivedData_, "Hello, World!", 14);
    }

    ~Derived() {  // 不是虚函数，且不会被调用！
        std::cout << "Derived destructor, freeing derivedData_\n";
        delete[] derivedData_;
    }

    void func() override {
        std::cout << "Derived::func, derivedData=" << derivedData_ << "\n";
    }
};

void testCase1_DirectDelete() {
    std::cout << "=== Case 1: 直接删除派生类指针 ===\n";
    Derived* d = new Derived();
    delete d;  // 正确：调用 ~Derived() 和 ~Base()
    std::cout << "Case 1: 内存已正确释放\n\n";
}

void testCase2_DeleteThroughBasePointer() {
    std::cout << "=== Case 2: 通过基类指针删除（危险！） ===\n";
    Base* b = new Derived();
    delete b;  // 危险！只调用 ~Base()，~Derived() 不会被调用
    std::cout << "Case 2: Derived的内存泄漏了！\n\n";
}

void testCase3_SmartPointerStillNeedsVirtualDtor() {
    std::cout << "=== Case 3: 智能指针仍需虚析构函数 ===\n";
    std::unique_ptr<Base> ptr = std::make_unique<Derived>();
    // 当ptr销毁时，仍只调用 ~Base()！
    std::cout << "Case 3: 即使使用智能指针，Derived的内存仍然泄漏！\n\n";
}

int main() {
    testCase1_DirectDelete();
    testCase2_DeleteThroughBasePointer();
    testCase3_SmartPointerStillNeedsVirtualDtor();

    return 0;
}
