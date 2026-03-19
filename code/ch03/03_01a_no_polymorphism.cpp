#include <iostream>
#include <string>
#include <vector>

// 枚举类型标识
enum class AnimalType {
    Dog,
    Cat,
    Bird
};

// 动物基类（不使用多态）
class Animal {
public:
    AnimalType type;
    std::string name;

    Animal(AnimalType t, const std::string& n) : type(t), name(n) {}

    void eat() {
        std::cout << name << " is eating.\n";
    }

    void sleep() {
        std::cout << name << " is sleeping.\n";
    }
};

class Dog : public Animal {
public:
    Dog(const std::string& n) : Animal(AnimalType::Dog, n) {}
    void bark() const { std::cout << name << " says: Woof!\n"; }
};

class Cat : public Animal {
public:
    Cat(const std::string& n) : Animal(AnimalType::Cat, n) {}
    void meow() const { std::cout << name << " says: Meow!\n"; }
};

class Bird : public Animal {
public:
    Bird(const std::string& n) : Animal(AnimalType::Bird, n) {}
    void chirp() const { std::cout << name << " says: Tweet!\n"; }
};

// 问题：需要类型分支判断
void makeAnimalSound(const Animal& animal) {
    // 每添加新类型，这里都要修改！
    switch (animal.type) {
        case AnimalType::Dog:
            static_cast<const Dog&>(animal).bark();
            break;
        case AnimalType::Cat:
            static_cast<const Cat&>(animal).meow();
            break;
        case AnimalType::Bird:
            static_cast<const Bird&>(animal).chirp();
            break;
    }
}

int main() {
    Dog dog("Buddy");
    Cat cat("Whiskers");
    Bird bird("Tweety");

    // 必须分别处理
    makeAnimalSound(dog);    // 输出: Buddy says: Woof!
    makeAnimalSound(cat);    // 输出: Whiskers says: Meow!
    makeAnimalSound(bird);   // 输出: Tweety says: Tweet!

    return 0;
}
