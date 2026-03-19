#include <iostream>
#include <memory>

// 抽象基类使用纯虚析构函数
class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void draw() const = 0;

    // 纯虚析构函数
    virtual ~Shape() = 0;
};

// 即使是纯虚函数，也必须提供实现！
Shape::~Shape() {
    std::cout << "Shape destructor\n";
}

class Circle : public Shape {
    double radius_;

public:
    Circle(double r) : radius_(r) {
        std::cout << "Circle constructor\n";
    }

    ~Circle() override {
        std::cout << "Circle destructor\n";
    }

    double area() const override {
        return 3.14159 * radius_ * radius_;
    }

    double perimeter() const override {
        return 2 * 3.14159 * radius_;
    }

    void draw() const override {
        std::cout << "Drawing Circle, radius=" << radius_ << "\n";
    }
};

int main() {
    std::cout << "=== 纯虚析构函数示例 ===\n\n";

    // Shape shape;  // 编译错误！不能实例化抽象类

    std::unique_ptr<Shape> shape = std::make_unique<Circle>(5.0);
    std::cout << "Area: " << shape->area() << "\n";
    shape->draw();

    // 销毁时自动调用 ~Circle() 和 ~Shape()
    return 0;
}
