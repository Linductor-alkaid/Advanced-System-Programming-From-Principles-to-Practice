#include <iostream>
#include <new>      // for ::operator new
#include <cstdlib>  // for free
#include <string>

class Widget {
    std::string name;
public:
    Widget(const std::string& n) : name(n) {
        std::cout << "构造: " << name << std::endl;
    }

    ~Widget() {
        std::cout << "析构: " << name << std::endl;
    }

    void greet() {
        std::cout << "Hello from " << name << std::endl;
    }
};

int main() {
    std::cout << "=== 普通堆对象 ===" << std::endl;
    Widget* p1 = new Widget("堆对象1");
    p1->greet();
    delete p1;  // 自动调用析构函数 + 释放内存

    std::cout << "\n=== placement new ===" << std::endl;
    // 手动分配内存（不调用构造函数）
    void* raw = ::operator new(sizeof(Widget));
    // 在已有内存上构造对象
    Widget* p2 = new(raw) Widget("栈上对象");
    p2->greet();

    // 必须手动调用析构函数！
    p2->~Widget();
    // 然后手动释放内存
    ::operator delete(raw);

    std::cout << "\n=== 对象数组 ===" << std::endl;

    Widget* arr = new Widget[3]{{"元素0"}, {"元素1"}, {"元素2"}};
    delete[] arr; // 调用3次析构函数 + 释放内存

    return 0;
}
