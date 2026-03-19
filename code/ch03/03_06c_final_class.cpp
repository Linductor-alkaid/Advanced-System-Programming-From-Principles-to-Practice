#include <iostream>

// 标记类为 final
class Utility final {
public:
    static void helper() {
        std::cout << "Utility::helper\n";
    }
};

// 错误：无法继承 final 类
// class ExtendedUtility : public Utility {  // 编译错误
// public:
//     void extraMethod();
// };

// 正确使用：通过组合而非继承
class ExtendedUtility {
    Utility util_;  // 组合
public:
    void helper() {
        util_.helper();  // 委托
    }

    void extraMethod() {
        std::cout << "Extra functionality\n";
    }
};

int main() {
    Utility::helper();  // 直接使用

    ExtendedUtility ext;
    ext.helper();       // 通过组合使用
    ext.extraMethod();

    return 0;
}
