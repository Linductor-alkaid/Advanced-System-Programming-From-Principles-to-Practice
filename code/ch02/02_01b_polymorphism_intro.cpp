#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Animal {
protected:
    std::string name_;

public:
    Animal(const std::string& name) : name_(name) {}
    virtual ~Animal() = default;

    // 虚函数：允许派生类重写
    virtual void makeSound() const {
        std::cout << name_ << " makes a sound.\n";
    }

    // 纯虚函数：要求派生类必须实现
    virtual std::string getSpecies() const = 0;
};

class Dog : public Animal {
public:
    Dog(const std::string& name) : Animal(name) {}

    void makeSound() const override {
        std::cout << name_ << " says: Woof!\n";
    }

    std::string getSpecies() const override {
        return "Dog";
    }
};

class Cat : public Animal {
public:
    Cat(const std::string& name) : Animal(name) {}

    void makeSound() const override {
        std::cout << name_ << " says: Meow!\n";
    }

    std::string getSpecies() const override {
        return "Cat";
    }
};

// 统一处理函数：可以接受任何派生类
void animalAction(const Animal& animal) {
    std::cout << "This is a " << animal.getSpecies() << ".\n";
    animal.makeSound();  // 多态调用：根据实际对象类型调用对应函数
}

int main() {
    Dog dog("Buddy");
    Cat cat("Whiskers");

    // 统一处理不同类型
    animalAction(dog);  // 输出: This is a Dog. Buddy says: Woof!
    animalAction(cat);  // 输出: This is a Cat. Whiskers says: Meow!

    // 使用容器存储基类指针
    std::vector<std::unique_ptr<Animal>> zoo;
    zoo.push_back(std::make_unique<Dog>("Max"));
    zoo.push_back(std::make_unique<Cat>("Mittens"));
    zoo.push_back(std::make_unique<Dog>("Rocky"));

    // 统一遍历处理
    std::cout << "\n--- Zoo Tour ---\n";
    for (const auto& animal : zoo) {
        animal->makeSound();
    }

    return 0;
}
