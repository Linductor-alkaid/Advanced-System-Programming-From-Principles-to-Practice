#include <iostream>
#include <vector>
#include <memory>
#include <string>

// 基类：所有图形的抽象
class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void draw() const {
        std::cout << "Drawing a shape\n";
    }
};

// 派生类：圆形是一种图形
class Circle : public Shape {
    double radius_;
public:
    Circle(double r) : radius_(r) {}

    double area() const override {
        return 3.14159 * radius_ * radius_;
    }

    double perimeter() const override {
        return 2 * 3.14159 * radius_;
    }

    void draw() const override {
        std::cout << "Drawing a circle with radius " << radius_ << "\n";
    }
};

// 派生类：矩形是一种图形
class Rectangle : public Shape {
    double width_, height_;
public:
    Rectangle(double w, double h) : width_(w), height_(h) {}

    double area() const override {
        return width_ * height_;
    }

    double perimeter() const override {
        return 2 * (width_ + height_);
    }

    void draw() const override {
        std::cout << "Drawing a rectangle " << width_ << "x" << height_ << "\n";
    }
};

// 统一处理所有图形
void processShapes(const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (const auto& shape : shapes) {
        shape->draw();
        std::cout << "  Area: " << shape->area() << "\n";
    }
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(3.0, 4.0));

    processShapes(shapes);

    return 0;
}
