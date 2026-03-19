#include <iostream>
#include <memory>

class Interface {
public:
    virtual void execute() = 0;
    virtual void configure() = 0;
    virtual ~Interface() = default;
};

class Implementation : public Interface {
public:
    void execute() override final {
        std::cout << "Implementation::execute - 最终实现\n";
    }

    void configure() override {
        std::cout << "Implementation::configure\n";
    }
};

class OptimizedImplementation : public Implementation {
public:
    // 错误：不能覆盖 final 函数
    // void execute() override {
    //     std::cout << "Optimized version\n";
    // }

    // 可以覆盖非 final 函数
    void configure() override {
        std::cout << "OptimizedImplementation::configure\n";
        Implementation::configure();
    }
};

// 完全禁止继承的类
class FinalImplementation final : public Interface {
public:
    void execute() override {
        std::cout << "FinalImplementation::execute\n";
    }

    void configure() override {
        std::cout << "FinalImplementation::configure\n";
    }
};

// 错误：不能继承 final 类
// class ExtendedFinal : public FinalImplementation { };

int main() {
    std::unique_ptr<Interface> impl = std::make_unique<OptimizedImplementation>();
    impl->execute();    // Implementation::execute
    impl->configure();  // OptimizedImplementation::configure

    std::unique_ptr<Interface> finalImpl = std::make_unique<FinalImplementation>();
    finalImpl->execute();

    return 0;
}
