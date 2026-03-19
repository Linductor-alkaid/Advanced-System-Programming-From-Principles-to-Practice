#include <iostream>
#include <memory>

// 简单的多态类
class Base {
public:
    virtual void func1() { std::cout << "Base::func1\n"; }
    virtual void func2() { std::cout << "Base::func2\n"; }
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    void func1() override { std::cout << "Derived::func1\n"; }
    virtual void func3() { std::cout << "Derived::func3\n"; }  // 新增虚函数
};

// 虚函数表指针类型：函数指针数组
using VTable = const void*[];

// 打印对象内存内容和vtable
void inspectObject(Base* obj) {
    std::cout << "=== Object Inspection ===\n";
    std::cout << "Object address: " << obj << "\n";

    // 读取vptr（对象的前8/4字节）
    const void** vptr_ptr = reinterpret_cast<const void**>(obj);
    const void* vptr = *vptr_ptr;
    std::cout << "vptr points to: " << vptr << "\n";

    // 访问vtable
    const VTable* vtable = reinterpret_cast<const VTable*>(vptr);

    // 打印vtable中的函数指针
    std::cout << "\nvtable contents:\n";
    for (int i = 0; i < 4; ++i) {
        std::cout << "  [" << i << "] " << (*vtable)[i] << "\n";
    }

    // 尝试调用vtable中的函数
    std::cout << "\nCalling through vtable:\n";
    using FuncType = void(*)(Base*);
    FuncType func = reinterpret_cast<FuncType>((*vtable)[1]);  // func1通常在偏移1
    func(obj);  // 通过vtable直接调用
}

int main() {
    Base b;
    Derived d;

    std::cout << "Base object:\n";
    std::cout << "sizeof(Base) = " << sizeof(Base) << "\n";
    inspectObject(&b);

    std::cout << "\n\nDerived object:\n";
    std::cout << "sizeof(Derived) = " << sizeof(Derived) << "\n";
    inspectObject(&d);

    return 0;
}
