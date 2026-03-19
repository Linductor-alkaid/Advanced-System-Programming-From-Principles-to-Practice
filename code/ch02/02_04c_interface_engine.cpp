#include <iostream>
#include <memory>
#include <string>

// 引擎接口
class IEngine {
public:
    virtual ~IEngine() = default;
    virtual void start() = 0;
    virtual void stop() = 0;
};

// 具体引擎实现
class GasEngine : public IEngine {
public:
    void start() override { std::cout << "Gas engine starting\n"; }
    void stop() override { std::cout << "Gas engine stopping\n"; }
};

class ElectricEngine : public IEngine {
public:
    void start() override { std::cout << "Electric engine starting\n"; }
    void stop() override { std::cout << "Electric engine stopping\n"; }
};

// Car通过组合持有引擎接口，支持多态
class Car {
    std::unique_ptr<IEngine> engine_;
    std::string brand_;

public:
    Car(const std::string& brand, std::unique_ptr<IEngine> engine)
        : brand_(brand), engine_(std::move(engine)) {}

    void start() {
        std::cout << brand_ << " starting...\n";
        engine_->start();
    }

    // 可以在运行时更换引擎
    void setEngine(std::unique_ptr<IEngine> newEngine) {
        engine_ = std::move(newEngine);
    }
};

int main() {
    Car car1("Tesla", std::make_unique<ElectricEngine>());
    car1.start();

    Car car2("Ford", std::make_unique<GasEngine>());
    car2.start();

    // 运行时更换引擎
    car1.setEngine(std::make_unique<GasEngine>());
    car1.start();

    return 0;
}
