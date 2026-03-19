#include <iostream>
#include <memory>
#include <cstring>
#include <vector>

// 正确：基类析构函数是虚函数
class Base {
public:
    int* baseData_;

    Base() : baseData_(new int(100)) {
        std::cout << "Base constructor, allocating baseData_\n";
    }

    virtual ~Base() {  // 虚析构函数
        std::cout << "Base destructor, freeing baseData_\n";
        delete baseData_;
    }

    virtual void func() {
        std::cout << "Base::func\n";
    }
};

class Derived : public Base {
public:
    char* derivedData_;

    Derived() : Base(), derivedData_(new char[1024]) {
        std::cout << "Derived constructor, allocating derivedData_\n";
        std::memcpy(derivedData_, "Hello, World!", 14);
    }

    ~Derived() override {  // override关键字（C++11）
        std::cout << "Derived destructor, freeing derivedData_\n";
        delete[] derivedData_;
    }

    void func() override {
        std::cout << "Derived::func, derivedData=" << derivedData_ << "\n";
    }
};

int main() {
    std::cout << "=== 正确使用虚析构函数 ===\n\n";

    std::cout << "场景1：通过基类指针删除\n";
    {
        Base* b = new Derived();
        delete b;  // 现在是安全的！
    }

    std::cout << "\n场景2：使用智能指针\n";
    {
        std::unique_ptr<Base> ptr = std::make_unique<Derived>();
        // 智能指针现在也能正确工作
    }

    std::cout << "\n场景3：多态容器\n";
    {
        std::vector<std::unique_ptr<Base>> objects;
        objects.push_back(std::make_unique<Derived>());
        objects.clear();  // 所有对象被正确析构
    }

    return 0;
}
