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
        std::cout << "Widget " << id << " 析构 (use_count=" << id << ")\n";
    }

    void doSomething() {
        std::cout << "Widget " << id << " 正在工作\n";
    }
};

void shared_ptr_demo() {
    std::cout << "=== 创建 shared_ptr ===\n";
    auto p1 = std::make_shared<Widget>(1);
    std::cout << "p1.use_count() = " << p1.use_count() << "\n";

    {
        std::cout << "\n=== 拷贝 shared_ptr ===\n";
        std::shared_ptr<Widget> p2 = p1;  // 拷贝，引用计数 +1
        std::cout << "p1.use_count() = " << p1.use_count() << "\n";
        std::cout << "p2.use_count() = " << p2.use_count() << "\n";

        std::cout << "\n=== 添加到容器 ===\n";
        std::vector<std::shared_ptr<Widget>> vec;
        vec.push_back(p1);  // 引用计数 +1
        std::cout << "p1.use_count() = " << p1.use_count() << "\n";

        std::cout << "\n=== 离开内部作用域 ===\n";
    }
    // p2 和 vec 中的元素被销毁，引用计数减少
    std::cout << "p1.use_count() = " << p1.use_count() << "\n";

    std::cout << "\n=== reset 操作 ===\n";
    p1.reset();  // 释放所有权
    std::cout << "p1.use_count() = " << p1.use_count() << "\n";
    std::cout << "p1 == nullptr: " << (p1 == nullptr) << "\n";

    std::cout << "\n=== 离开作用域 ===\n";
}

int main() {
    shared_ptr_demo();
    return 0;
}
