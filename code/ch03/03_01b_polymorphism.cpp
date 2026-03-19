#include <iostream>
#include <string>
#include <vector>
#include <memory>

// 多态基类：定义统一接口
class Animal {
protected:
    std::string name_;

public:
    Animal(const std::string& name) : name_(name) {}
    virtual ~Animal() = default;  // 虚析构函数（后面详讲）

    // 统一接口：虚函数
    virtual void makeSound() const = 0;  // 纯虚函数

    // 非虚函数：所有派生类共享的行为
    void eat() const {
        std::cout << name_ << " is eating.\n";
    }

    void sleep() const {
        std::cout << name_ << " is sleeping.\n";
    }

    std::string getName() const { return name_; }
};

// 派生类：实现具体行为
class Dog : public Animal {
public:
    Dog(const std::string& name) : Animal(name) {}

    void makeSound() const override {
        std::cout << name_ << " says: Woof!\n";
    }

    void fetch() const {
        std::cout << name_ << " is fetching the ball!\n";
    }
};

class Cat : public Animal {
public:
    Cat(const std::string& name) : Animal(name) {}

    void makeSound() const override {
        std::cout << name_ << " says: Meow!\n";
    }

    void scratch() const {
        std::cout << name_ << " is scratching the furniture!\n";
    }
};

class Bird : public Animal {
public:
    Bird(const std::string& name) : Animal(name) {}

    void makeSound() const override {
        std::cout << name_ << " says: Tweet!\n";
    }

    void fly() const {
        std::cout << name_ << " is flying high!\n";
    }
};

// 统一处理函数：无需类型判断！
void animalSound(const Animal& animal) {
    animal.makeSound();  // 多态调用
}

// 统一处理容器
void zooTour(const std::vector<std::unique_ptr<Animal>>& zoo) {
    std::cout << "\n=== Zoo Tour ===\n";
    for (const auto& animal : zoo) {
        std::cout << "Visiting " << animal->getName() << ": ";
        animal->makeSound();  // 多态调用
    }
}

int main() {
    Dog dog("Buddy");
    Cat cat("Whiskers");
    Bird bird("Tweety");

    // 统一接口调用
    animalSound(dog);    // 输出: Buddy says: Woof!
    animalSound(cat);    // 输出: Whiskers says: Meow!
    animalSound(bird);   // 输出: Tweety says: Tweet!

    // 使用容器统一存储
    std::vector<std::unique_ptr<Animal>> zoo;
    zoo.push_back(std::make_unique<Dog>("Max"));
    zoo.push_back(std::make_unique<Cat>("Mittens"));
    zoo.push_back(std::make_unique<Bird>("Polly"));
    zoo.push_back(std::make_unique<Dog>("Rocky"));

    zooTour(zoo);

    return 0;
}
