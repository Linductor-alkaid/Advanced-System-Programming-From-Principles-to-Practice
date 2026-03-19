#include <iostream>
#include <string>

class Member {
    std::string name;
public:
    Member(const std::string& n) : name(n) {
        std::cout << "  Member构造: " << name << std::endl;
    }

    ~Member() {
        std::cout << "  Member析构: " << name << std::endl;
    }
};

class Base {
public:
    Base() {
        std::cout << "  Base构造" << std::endl;
    }

    virtual ~Base() {
        std::cout << "  Base析构" << std::endl;
    }
};

class Derived : public Base {
    Member m1;  // 注意：声明顺序是 m1, m2, m3
    Member m2;
    Member m3;
public:
    Derived() : m2("m2"), m1("m1"), m3("m3") {  // 初始化列表顺序不影响
        std::cout << "  Derived构造" << std::endl;
    }

    ~Derived() {
        std::cout << "  Derived析构" << std::endl;
    }
};

int main() {
    std::cout << "创建 Derived 对象:" << std::endl;
    Derived obj;
    std::cout << "\n销毁 Derived 对象:" << std::endl;
    return 0;
}
