#include <iostream>
#include <cstdint>

class A {
public:
    int a;
private:
    int b;
public:
    int c;
};

class B {
public:
    int a;
    int b;  // 注意：这里是public
    int c;
};

int main() {
    std::cout << "sizeof(A) = " << sizeof(A) << std::endl;
    std::cout << "sizeof(B) = " << sizeof(B) << std::endl;

    A objA;
    objA.a = 1;
    objA.c = 3;
    B objB{10, 20, 30};

    // 打印内存
    auto printMem = [](const void* p, size_t n) {
        const uint8_t* bytes = static_cast<const uint8_t*>(p);
        for (size_t i = 0; i < n; ++i) {
            std::cout << static_cast<int>(bytes[i]) << " ";
        }
        std::cout << std::endl;
    };

    std::cout << "\nA的内存: ";
    printMem(&objA, sizeof(A));

    std::cout << "B的内存: ";
    printMem(&objB, sizeof(B));

    return 0;
}
