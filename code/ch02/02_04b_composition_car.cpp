#include <iostream>
#include <string>

// Engine是一个独立的类
class Engine {
    std::string model_;
public:
    Engine(const std::string& model) : model_(model) {}

    void start() {
        std::cout << "Engine " << model_ << " starting...\n";
    }

    void stop() {
        std::cout << "Engine " << model_ << " stopping...\n";
    }

    std::string getModel() const { return model_; }
};

// Car有一个Engine（不是is-a关系）
class Car {
    Engine engine_;
    std::string brand_;
public:
    Car(const std::string& brand, const std::string& engineModel)
        : engine_(engineModel), brand_(brand) {}

    void start() {
        std::cout << brand_ << " car starting...\n";
        engine_.start();
    }

    void stop() {
        engine_.stop();
        std::cout << brand_ << " car stopped.\n";
    }

    void replaceEngine(const std::string& newModel) {
        engine_ = Engine(newModel);  // 可以在运行时更换
        std::cout << "Engine replaced with " << newModel << "\n";
    }
};

int main() {
    Car car("Toyota", "V6");

    car.start();
    car.stop();

    car.replaceEngine("Electric");

    return 0;
}
