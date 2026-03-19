#include <iostream>
#include <cstddef>
#include <iomanip>

// 带有成员变量的基类
class Base {
public:
    int baseData_;
    virtual void func1() { std::cout << "Base::func1, baseData=" << baseData_ << "\n"; }
    virtual void func2() { std::cout << "Base::func2\n"; }
    virtual ~Base() { std::cout << "Base::~Base\n"; }

    Base(int data) : baseData_(data) {}
};

class Derived : public Base {
public:
    int derivedData_;

    Derived(int baseData, int derivedData)
        : Base(baseData), derivedData_(derivedData) {}

    void func1() override {
        std::cout << "Derived::func1, baseData=" << baseData_
                  << ", derivedData=" << derivedData_ << "\n";
    }

    virtual void func3() {  // 新增虚函数
        std::cout << "Derived::func3\n";
    }
};

void printMemoryLayout(const char* name, const void* obj, size_t size) {
    const unsigned char* bytes = static_cast<const unsigned char*>(obj);
    std::cout << name << " memory layout (" << size << " bytes):\n";

    for (size_t i = 0; i < size; ++i) {
        if (i % 8 == 0) std::cout << "  ";
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)bytes[i] << " ";
        if ((i + 1) % 8 == 0) std::cout << "\n";
    }
    std::cout << "\n";

    // 解释内存布局
    std::cout << "Layout explanation:\n";
    std::cout << "  Bytes 0-7:  vptr (pointer to vtable)\n";
    if (size >= 16) {
        std::cout << "  Bytes 8-15: Base class members (baseData_)\n";
    }
    if (size >= 24) {
        std::cout << "  Bytes 16-23: Derived class members (derivedData_)\n";
    }
    std::cout << "\n";
}

int main() {
    std::cout << "Size information:\n";
    std::cout << "  sizeof(Base) = " << sizeof(Base) << " bytes\n";
    std::cout << "  sizeof(Derived) = " << sizeof(Derived) << " bytes\n";
    std::cout << "  sizeof(void*) = " << sizeof(void*) << " bytes\n\n";

    Base b(42);
    Derived d(100, 200);

    printMemoryLayout("Base object", &b, sizeof(b));
    printMemoryLayout("Derived object", &d, sizeof(d));

    // 验证vptr的位置
    std::cout << "Verification:\n";
    const void** vptr_ptr = reinterpret_cast<const void**>(&d);
    std::cout << "  vptr is at the start of the object: " << *vptr_ptr << "\n";

    return 0;
}
