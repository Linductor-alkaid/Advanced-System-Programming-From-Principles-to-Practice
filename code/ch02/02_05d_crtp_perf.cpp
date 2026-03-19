#include <iostream>
#include <chrono>
#include <vector>

// ========== 虚函数版本 ==========
class ShapeVirtual {
public:
    virtual ~ShapeVirtual() = default;
    virtual double area() const = 0;
};

class CircleVirtual : public ShapeVirtual {
    double radius_;
public:
    CircleVirtual(double r) : radius_(r) {}
    double area() const override { return 3.14159 * radius_ * radius_; }
};

// ========== CRTP 版本 ==========
template <typename Derived>
class ShapeCRTP {
public:
    double area() const {
        return static_cast<const Derived*>(this)->areaImpl();
    }
};

class CircleCRTP : public ShapeCRTP<CircleCRTP> {
    double radius_;
public:
    CircleCRTP(double r) : radius_(r) {}
    double areaImpl() const { return 3.14159 * radius_ * radius_; }
};

// ========== 性能测试 ==========
constexpr size_t ITERATIONS = 100'000'000;
constexpr double RADIUS = 5.0;

void benchmarkVirtual() {
    CircleVirtual circle(RADIUS);
    double sum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < ITERATIONS; ++i) {
        sum += circle.area();
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Virtual: " << duration.count() << "ms, sum=" << sum << "\n";
}

void benchmarkCRTP() {
    CircleCRTP circle(RADIUS);
    double sum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < ITERATIONS; ++i) {
        sum += circle.area();
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "CRTP: " << duration.count() << "ms, sum=" << sum << "\n";
}

int main() {
    std::cout << "Performance comparison (" << ITERATIONS << " iterations):\n";

    // 多次运行以稳定结果
    for (int i = 0; i < 3; ++i) {
        std::cout << "\nRound " << (i + 1) << ":\n";
        benchmarkVirtual();
        benchmarkCRTP();
    }

    // 典型输出（优化编译下）：
    // Virtual: 120ms (虚函数调用)
    // CRTP: 0ms (完全内联优化)

    return 0;
}
