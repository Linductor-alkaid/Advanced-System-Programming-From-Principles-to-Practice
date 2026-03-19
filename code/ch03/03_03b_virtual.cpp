#include <iostream>
#include <string>
#include <vector>
#include <memory>

// 使用虚函数实现多态
class Animal {
public:
    std::string name_;

    Animal(const std::string& name) : name_(name) {}

    // 虚函数：允许派生类重写
    virtual void speak() {
        std::cout << name_ << " makes a sound.\n";
    }

    // 虚析构函数：确保正确析构派生类
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    Dog(const std::string& name) : Animal(name) {}

    // override关键字：明确表示重写基类虚函数
    void speak() override {
        std::cout << name_ << " says: Woof!\n";
    }
};

class Cat : public Animal {
public:
    Cat(const std::string& name) : Animal(name) {}

    void speak() override {
        std::cout << name_ << " says: Meow!\n";
    }
};

// 统一处理函数：多态调用
void makeAnimalSpeak(Animal& animal) {
    animal.speak();  // 根据实际对象类型调用对应函数
}

int main() {
    Dog dog("Buddy");
    Cat cat("Whiskers");

    dog.speak();   // 输出: Buddy says: Woof!
    cat.speak();   // 输出: Whiskers says: Meow!

    // 通过基类引用调用，多态正常工作
    Animal& animalRef1 = dog;
    Animal& animalRef2 = cat;
    animalRef1.speak();  // 输出: Buddy says: Woof!
    animalRef2.speak();  // 输出: Whiskers says: Meow!

    makeAnimalSpeak(dog);  // 输出: Buddy says: Woof!
    makeAnimalSpeak(cat);  // 输出: Whiskers says: Meow!

    // 多态容器
    std::vector<std::unique_ptr<Animal>> zoo;
    zoo.push_back(std::make_unique<Dog>("Max"));
    zoo.push_back(std::make_unique<Cat>("Mittens"));
    zoo.push_back(std::make_unique<Dog>("Rocky"));

    std::cout << "\n=== Zoo Tour ===\n";
    for (const auto& animal : zoo) {
        animal->speak();  // 多态调用
    }

    return 0;
}
