#include <iostream>

class Base {
public:
    virtual void process(int x, int y) {
        std::cout << "Base::process(" << x << ", " << y << ")\n";
    }

    virtual void getData() const {
        std::cout << "Base::getData const\n";
    }

    virtual void processRef() & {
        std::cout << "Base::processRef &\n";
    }

    virtual ~Base() = default;
};

// 以下三个派生类演示 override 如何检查签名匹配
// 它们都会导致编译错误，因此注释掉：

// 错误1：参数类型不同
// class Derived1 : public Base {
// public:
//     void process(int x, double y) override {  // 错误！int vs double
//         std::cout << "Derived1::process\n";
//     }
// };

// 错误2：缺少 const
// class Derived2 : public Base {
// public:
//     void getData() override {  // 错误！缺少 const
//         std::cout << "Derived2::getData\n";
//     }
// };

// 错误3：引用限定符不同
// class Derived3 : public Base {
// public:
//     void processRef() && override {  // 错误！& vs &&
//         std::cout << "Derived3::processRef\n";
//     }
// };

// 正确：签名完全匹配
class DerivedCorrect : public Base {
public:
    void process(int x, int y) override {
        std::cout << "DerivedCorrect::process(" << x << ", " << y << ")\n";
    }

    void getData() const override {
        std::cout << "DerivedCorrect::getData const\n";
    }

    void processRef() & override {
        std::cout << "DerivedCorrect::processRef &\n";
    }
};

int main() {
    DerivedCorrect d;
    d.process(1, 2);     // DerivedCorrect::process(1, 2)
    d.getData();         // DerivedCorrect::getData const
    d.processRef();      // DerivedCorrect::processRef &

    return 0;
}
