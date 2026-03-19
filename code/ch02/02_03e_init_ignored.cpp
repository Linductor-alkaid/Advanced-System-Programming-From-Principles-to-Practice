#include <iostream>

class Base {
public:
    Base(int x) : val(x) {}
    int val;
};

class Derived : virtual public Base {
public:
    Derived() : Base(100) {  // 这个初始化会被忽略！
        std::cout << "Derived: Base::val = " << val << "\n";
    }
};

class MostDerived : public Derived {
public:
    MostDerived() : Base(999) {  // 只有这里有效
        std::cout << "MostDerived: Base::val = " << val << "\n";
    }
};

int main() {
    MostDerived md;
    // 输出: MostDerived: Base::val = 999
    // Derived中的 Base(100) 被忽略了
}
