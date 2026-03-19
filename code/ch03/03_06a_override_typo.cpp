#include <iostream>

class Base {
public:
    virtual void process() {
        std::cout << "Base::process\n";
    }

    virtual ~Base() = default;
};

// 错误演示：没有 override，拼写错误不会被发现
class DerivedWrong : public Base {
public:
    void proccess() {  // 拼写错误！process -> proccess
        std::cout << "DerivedWrong::proccess\n";
    }
};

// 正确做法：使用 override
// 以下代码会导致编译错误，因此注释掉以演示效果：
// class DerivedRight : public Base {
// public:
//     void proccess() override {  // 编译错误！没有 Base::proccess
//         std::cout << "DerivedRight::proccess\n";
//     }
// };

int main() {
    Base* b1 = new DerivedWrong();
    b1->process();  // 输出: Base::process （而不是期望的派生类版本）

    // 使用 override 后，DerivedRight 根本无法编译通过
    // 这正是 override 的价值：在编译期发现拼写错误

    delete b1;
    return 0;
}
