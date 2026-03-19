#include <iostream>
#include <chrono>
#include <vector>

// 有虚析构函数的类
class VirtualDtor {
public:
    int data_;
    VirtualDtor(int d = 0) : data_(d) {}
    virtual ~VirtualDtor() {}
};

// 没有虚析构函数的类
class NonVirtualDtor {
public:
    int data_;
    NonVirtualDtor(int d = 0) : data_(d) {}
    ~NonVirtualDtor() {}
};

constexpr size_t N = 10'000'000;

void benchmarkWithVirtual() {
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i) {
        VirtualDtor* obj = new VirtualDtor(i);
        delete obj;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "With virtual dtor: " << duration.count() << "ms\n";
}

void benchmarkWithoutVirtual() {
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i) {
        NonVirtualDtor* obj = new NonVirtualDtor(i);
        delete obj;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Without virtual dtor: " << duration.count() << "ms\n";
}

int main() {
    std::cout << "虚析构函数性能测试 (" << N << " 次分配/释放):\n\n";

    benchmarkWithVirtual();
    benchmarkWithoutVirtual();

    std::cout << "\n说明：虚析构函数的开销主要来自：\n";
    std::cout << "1. vptr存储的空间开销（每个对象+8字节）\n";
    std::cout << "2. 查表的时间开销（可通过内联优化部分抵消）\n";
    std::cout << "3. 对于大多数应用，这个开销是可以接受的\n";

    return 0;
}
