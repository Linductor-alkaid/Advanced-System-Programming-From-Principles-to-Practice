#include <iostream>

// CRTP 单例基类
template <typename Derived>
class Singleton {
public:
    static Derived& getInstance() {
        static Derived instance;
        return instance;
    }

    // 删除拷贝和移动
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

protected:
    Singleton() = default;
    ~Singleton() = default;
};

// 使用 CRTP 的单例
class MyManager : public Singleton<MyManager> {
    // 让基类能访问构造函数
    friend class Singleton<MyManager>;

private:
    MyManager() {
        std::cout << "MyManager initialized\n";
    }

    int data_ = 0;

public:
    void doSomething() {
        std::cout << "Manager working, data = " << data_ << "\n";
    }

    void setData(int value) { data_ = value; }
};

int main() {
    // 获取单例
    MyManager& mgr = MyManager::getInstance();
    mgr.setData(42);
    mgr.doSomething();

    // 同一个实例
    MyManager& mgr2 = MyManager::getInstance();
    mgr2.doSomething();  // data 仍是 42

    return 0;
}
