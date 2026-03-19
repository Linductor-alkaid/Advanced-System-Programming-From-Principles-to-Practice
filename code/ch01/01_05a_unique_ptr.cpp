#include <iostream>
#include <memory>
#include <vector>

class Widget {
    int id;
public:
    explicit Widget(int i) : id(i) {
        std::cout << "Widget " << id << " 构造\n";
    }

    ~Widget() {
        std::cout << "Widget " << id << " 析构\n";
    }

    void doSomething() {
        std::cout << "Widget " << id << " 正在工作\n";
    }
};

void unique_ptr_demo() {
    std::cout << "=== 创建 unique_ptr ===\n";

    // 方式1：使用 new（不推荐）
    std::unique_ptr<Widget> p1(new Widget(1));

    // 方式2：使用 make_unique（推荐，C++14）
    auto p2 = std::make_unique<Widget>(2);

    std::cout << "\n=== 访问对象 ===\n";
    p1->doSomething();       // 使用 -> 运算符
    (*p2).doSomething();     // 使用 * 运算符

    std::cout << "\n=== 所有权转移 ===\n";
    std::unique_ptr<Widget> p3 = std::move(p1);  // p1 变为空
    // p1->doSomething();  // 错误！p1 已经是 nullptr

    if (p1) {
        std::cout << "p1 非空\n";
    } else {
        std::cout << "p1 为空（所有权已转移）\n";
    }

    p3->doSomething();

    std::cout << "\n=== 容器中使用 ===\n";
    std::vector<std::unique_ptr<Widget>> vec;
    vec.push_back(std::make_unique<Widget>(3));
    vec.push_back(std::make_unique<Widget>(4));

    // 移动语义：将 p2 转移到容器中
    vec.push_back(std::move(p2));

    std::cout << "\n=== 离开作用域 ===\n";
    // 所有 unique_ptr 自动析构
}

int main() {
    unique_ptr_demo();
    return 0;
}
