#include <iostream>
#include <cstdint>
#include <cstdio>

class Base {
public:
    int baseData1;
    long baseData2;

    Base() : baseData1(1), baseData2(2) {
        std::cout << "Base constructed\n";
    }

    virtual void func() {
        std::cout << "Base::func\n";
    }
};

class Derived : public Base {
public:
    int derivedData1;
    char derivedData2;

    Derived() : derivedData1(3), derivedData2('X') {
        std::cout << "Derived constructed\n";
    }

    void func() override {
        std::cout << "Derived::func\n";
    }
};

void printMemoryLayout(const void* obj, size_t size) {
    const uint8_t* bytes = static_cast<const uint8_t*>(obj);

    std::cout << "Memory dump (hex):\n";
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
    std::cout << "=== Single Inheritance Memory Layout ===\n\n";

    std::cout << "sizeof(Base) = " << sizeof(Base) << "\n";
    std::cout << "sizeof(Derived) = " << sizeof(Derived) << "\n\n";

    Derived d;
    d.baseData1 = 0x11111111;
    d.baseData2 = 0x2222222222222222;
    d.derivedData1 = 0x33333333;
    d.derivedData2 = 'X';

    std::cout << "Derived object memory layout:\n";
    printMemoryLayout(&d, sizeof(Derived));

    std::cout << "\nField offsets:\n";
    std::cout << "  vptr*:       offset = " << (char*)&d - (char*)&d << " (address: " << &d << ")\n";
    std::cout << "  baseData1:   offset = " << (char*)&d.baseData1 - (char*)&d << "\n";
    std::cout << "  baseData2:   offset = " << (char*)&d.baseData2 - (char*)&d << "\n";
    std::cout << "  derivedData1: offset = " << (char*)&d.derivedData1 - (char*)&d << "\n";
    std::cout << "  derivedData2: offset = " << (char*)&d.derivedData2 - (char*)&d << "\n";

    // 验证vptr的存在
    using VPtrType = void*;
    VPtrType vptr = *(VPtrType*)&d;
    std::cout << "\n  vptr value = 0x" << std::hex << vptr << std::dec << "\n";

    return 0;
}
