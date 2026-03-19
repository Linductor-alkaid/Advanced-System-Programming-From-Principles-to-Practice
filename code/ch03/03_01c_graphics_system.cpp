#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

const double PI = 3.14159265358979323846;

// 图形基类
class Shape {
protected:
    double x_, y_;  // 位置

public:
    Shape(double x, double y) : x_(x), y_(y) {}
    virtual ~Shape() = default;

    // 统一接口
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void draw() const = 0;

    void move(double dx, double dy) {
        x_ += dx;
        y_ += dy;
        std::cout << "Shape moved to (" << x_ << ", " << y_ << ")\n";
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

class Triangle : public Shape {
    double a_, b_, c_;  // 三边长

public:
    Triangle(double x, double y, double a, double b, double c)
        : Shape(x, y), a_(a), b_(b), c_(c) {}

    double area() const override {
        // 海伦公式
        double s = (a_ + b_ + c_) / 2;
        return std::sqrt(s * (s - a_) * (s - b_) * (s - c_));
    }

    double perimeter() const override {
        return a_ + b_ + c_;
    }

    void draw() const override {
        std::cout << "Drawing Triangle at (" << x_ << ", " << y_
                  << ") sides: " << a_ << ", " << b_ << ", " << c_ << "\n";
    }
};

// 统一处理：计算总面积
double totalArea(const std::vector<std::unique_ptr<Shape>>& shapes) {
    double sum = 0;
    for (const auto& shape : shapes) {
        sum += shape->area();  // 多态调用
    }
    return sum;
}

// 统一处理：绘制所有图形
void drawAll(const std::vector<std::unique_ptr<Shape>>& shapes) {
    std::cout << "\n=== Drawing All Shapes ===\n";
    for (const auto& shape : shapes) {
        shape->draw();  // 多态调用
    }
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Rectangle>(0, 0, 5, 3));
    shapes.push_back(std::make_unique<Circle>(10, 10, 2));
    shapes.push_back(std::make_unique<Triangle>(5, 5, 3, 4, 5));

    drawAll(shapes);

    std::cout << "\nTotal Area: " << totalArea(shapes) << "\n";

    // 统一移动所有图形
    for (auto& shape : shapes) {
        shape->move(1, 1);
    }

    return 0;
}
