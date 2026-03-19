#include <iostream>
#include <memory>
#include <string>

// 前向声明
class Child;

class Parent {
    std::string name;
    std::shared_ptr<Child> child;  // 父亲拥有孩子

public:
    explicit Parent(const std::string& n) : name(n) {
        std::cout << name << " (Parent) 构造\n";
    }

    ~Parent() {
        std::cout << name << " (Parent) 析构\n";
    }

    void setChild(std::shared_ptr<Child> c) {
        child = c;
    }

    const std::string& getName() const { return name; }
};

class Child {
    std::string name;
    // ✅ 使用 weak_ptr 打破循环
    std::weak_ptr<Parent> parent;

public:
    explicit Child(const std::string& n) : name(n) {
        std::cout << name << " (Child) 构造\n";
    }

    ~Child() {
        std::cout << name << " (Child) 析构\n";
    }

    void setParent(std::shared_ptr<Parent> p) {
        parent = p;
    }

    void doSomething() {
        // 使用 lock() 获取 shared_ptr，如果对象已销毁则返回空
        if (auto p = parent.lock()) {
            std::cout << name << " 的父亲是 " << p->getName() << "\n";
        } else {
            std::cout << name << " 的父亲已经不在了\n";
        }
    }
};

void circular_ref_demo() {
    std::cout << "=== 创建父节点 ===\n";
    auto parent = std::make_shared<Parent>("父亲");

    std::cout << "\n=== 创建子节点 ===\n";
    auto child = std::make_shared<Child>("儿子");

    std::cout << "\n=== 建立双向关系 ===\n";
    parent->setChild(child);   // Parent 强引用 Child
    child->setParent(parent);  // Child 弱引用 Parent

    std::cout << "Parent.use_count() = " << parent.use_count() << "\n";
    std::cout << "Child.use_count() = " << child.use_count() << "\n";

    child->doSomething();

    std::cout << "\n=== 离开作用域 ===\n";
    // 由于 Child 使用 weak_ptr，不会产生循环引用
    // 所有对象都能正确析构
}

int main() {
    circular_ref_demo();
    return 0;
}
