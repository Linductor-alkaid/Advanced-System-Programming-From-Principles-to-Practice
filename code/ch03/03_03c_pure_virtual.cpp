#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>

const double PI = 3.14159265358979323846;

// 抽象基类：包含纯虚函数
class Shape {
protected:
    double x_, y_;  // 位置

public:
    Shape(double x, double y) : x_(x), y_(y) {}
    virtual ~Shape() = default;  // 虚析构函数

    // 纯虚函数：没有实现，要求派生类必须实现
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void draw() const = 0;

    // 普通虚函数：提供默认实现，派生类可选择重写
    virtual void move(double dx, double dy) {
        x_ += dx;
        y_ += dy;
    }

    void getPosition() const {
        std::cout << "Position: (" << x_ << ", " << y_ << ")\n";
    }
};

class Rectangle : public Shape {
    double width_, height_;

public:
    Rectangle(double x, double y, double w, double h)
        : Shape(x, y), width_(w), height_(h) {}

    double area() const override {
        return width_ * height_;
    }

    double perimeter() const override {
        return 2 * (width_ + height_);
    }

    void draw() const override {
        std::cout << "Drawing Rectangle at (" << x_ << ", " << y_
                  << ") size: " << width_ << "x" << height_ << "\n";
    }
};

class Circle : public Shape {
    double radius_;

public:
    Circle(double x, double y, double r)
        : Shape(x, y), radius_(r) {}

    double area() const override {
        return PI * radius_ * radius_;
    }

    double perimeter() const override {
        return 2 * PI * radius_;
    }

    void draw() const override {
        std::cout << "Drawing Circle at (" << x_ << ", " << y_
                  << ") radius: " << radius_ << "\n";
    }
};

// 计算总面积：多态实现
double totalArea(const std::vector<std::unique_ptr<Shape>>& shapes) {
    double sum = 0;
    for (const auto& shape : shapes) {
        sum += shape->area();  // 多态调用
    }
    return sum;
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Rectangle>(0, 0, 5, 3));
    shapes.push_back(std::make_unique<Circle>(10, 10, 2));
    shapes.push_back(std::make_unique<Rectangle>(5, 5, 4, 4));

    std::cout << "Drawing all shapes:\n";
    for (const auto& shape : shapes) {
        shape->draw();  // 多态调用
    }

    std::cout << "\nTotal area: " << totalArea(shapes) << "\n";

    // Shape shape;  // 编译错误！不能实例化抽象类

    return 0;
}
