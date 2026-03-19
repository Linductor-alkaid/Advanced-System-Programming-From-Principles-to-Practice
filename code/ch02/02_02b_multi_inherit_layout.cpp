#include <iostream>
#include <cstdint>
#include <cstdio>

class Base1 {
public:
    int base1Data;
    virtual void func1() { std::cout << "Base1::func1\n"; }
};

class Base2 {
public:
    int base2Data;
    virtual void func2() { std::cout << "Base2::func2\n"; }
};

class Derived : public Base1, public Base2 {
public:
    int derivedData;

    Derived() : Base1(), Base2(), derivedData(3) {
        base1Data = 1;
        base2Data = 2;
    }

    void func1() override { std::cout << "Derived::func1\n"; }
    void func2() override { std::cout << "Derived::func2\n"; }
};

void printMemoryLayout(const void* obj, size_t size) {
    const uint8_t* bytes = static_cast<const uint8_t*>(obj);

    for (size_t i = 0; i < size; i += 8) {
        std::cout << "  offset 0x" << std::hex << i << ": ";
        for (size_t j = 0; j < 8 && i + j < size; ++j) {
            printf("%02x ", bytes[i + j]);
        }
        std::cout << "\n";
    }
    std::cout << std::dec;
}

int main() {
    std::cout << "=== Multiple Inheritance Memory Layout ===\n\n";

    std::cout << "sizeof(Base1) = " << sizeof(Base1) << "\n";
    std::cout << "sizeof(Base2) = " << sizeof(Base2) << "\n";
    std::cout << "sizeof(Derived) = " << sizeof(Derived) << "\n\n";

    Derived d;

    std::cout << "Derived object memory layout:\n";
    printMemoryLayout(&d, sizeof(Derived));

    std::cout << "\nField offsets:\n";
    std::cout << "  Derived*  : " << &d << "\n";
    std::cout << "  Base1*    : " << static_cast<Base1*>(&d) << " (offset: +"
              << (char*)static_cast<Base1*>(&d) - (char*)&d << ")\n";
    std::cout << "  Base2*    : " << static_cast<Base2*>(&d) << " (offset: +"
              << (char*)static_cast<Base2*>(&d) - (char*)&d << ")\n";
    std::cout << "  base1Data : offset +" << (char*)&d.base1Data - (char*)&d << "\n";
    std::cout << "  base2Data : offset +" << (char*)&d.base2Data - (char*)&d << "\n";
    std::cout << "  derivedData: offset +" << (char*)&d.derivedData - (char*)&d << "\n";

    return 0;
}
