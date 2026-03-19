#include <iostream>
#include <string>
#include <vector>

// 没有使用虚函数
class Animal {
public:
    std::string name_;

    Animal(const std::string& name) : name_(name) {}

    void speak() {
        std::cout << name_ << " makes a sound.\n";
    }
};

class Dog : public Animal {
public:
    Dog(const std::string& name) : Animal(name) {}

    void speak() {
        std::cout << name_ << " says: Woof!\n";
    }
};

class Cat : public Animal {
public:
    Cat(const std::string& name) : Animal(name) {}

    void speak() {
        std::cout << name_ << " says: Meow!\n";
    }
};

// 问题：无法实现多态
void makeAnimalSpeak(Animal& animal) {
    animal.speak();  // 总是调用 Animal::speak()
}

int main() {
    Dog dog("Buddy");
    Cat cat("Whiskers");

    dog.speak();   // 输出: Buddy says: Woof!
    cat.speak();   // 输出: Whiskers says: Meow!

    // 通过基类引用调用，多态失效
    Animal& animalRef1 = dog;
    Animal& animalRef2 = cat;
    animalRef1.speak();  // 输出: Buddy makes a sound. (不是Woof!)
    animalRef2.speak();  // 输出: Whiskers makes a sound. (不是Meow!)

    return 0;
}
