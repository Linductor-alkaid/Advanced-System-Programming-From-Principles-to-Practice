#include <chrono>
#include <iostream>

class Base {
public:
    virtual int func(int x) { return x * 2; }
};

class Derived : public Base {
public:
    int func(int x) override { return x * 3; }
};

// 非虚函数版本
class BaseStatic {
public:
    int func(int x) { return x * 2; }
};

class DerivedStatic : public BaseStatic {
public:
    int func(int x) { return x * 3; }
};

constexpr size_t ITERATIONS = 100'000'000;

void benchmarkVirtual() {
    Derived d;
    Base* ptr = &d;
    int sum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < ITERATIONS; ++i) {
        sum += ptr->func(i % 100);
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Virtual call: " << duration.count() << "ms, sum=" << sum << "\n";
}

void benchmarkStatic() {
    DerivedStatic d;
    DerivedStatic* ptr = &d;
    int sum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < ITERATIONS; ++i) {
        sum += ptr->func(i % 100);
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Static call: " << duration.count() << "ms, sum=" << sum << "\n";
}

int main() {
    std::cout << "Performance comparison (" << ITERATIONS << " iterations):\n";
    benchmarkVirtual();
    benchmarkStatic();

    return 0;
}
