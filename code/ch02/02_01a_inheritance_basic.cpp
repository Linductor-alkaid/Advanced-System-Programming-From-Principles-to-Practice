#include <iostream>
#include <string>

// 基类：定义所有动物共有的属性和行为
class Animal {
protected:  // 使用protected使派生类可以直接访问
    std::string name_;
    int age_;

public:
    Animal(const std::string& name, int age) : name_(name), age_(age) {}

    // 获取名字和年龄的接口
    std::string getName() const { return name_; }
    int getAge() const { return age_; }

    // 所有动物的共同行为
    void eat() {
        std::cout << name_ << " is eating.\n";
    }

    void sleep() {
        std::cout << name_ << " is sleeping.\n";
    }

    // 可以被子类覆盖的虚函数（多态基础，下一章详讲）
    virtual void makeSound() {
        std::cout << name_ << " makes a sound.\n";
    }

    // 虚析构函数（重要！防止内存泄漏）
    virtual ~Animal() = default;
};

// 派生类：Dog，只需添加自己特有的行为
class Dog : public Animal {
public:
    Dog(const std::string& name, int age) : Animal(name, age) {}

    void bark() {
        std::cout << name_ << " says: Woof!\n";
    }

    // 重写基类的makeSound
    void makeSound() override {
        bark();
    }
};

// 派生类：Cat，只需添加自己特有的行为
class Cat : public Animal {
public:
    Cat(const std::string& name, int age) : Animal(name, age) {}

    void meow() {
        std::cout << name_ << " says: Meow!\n";
    }

    void makeSound() override {
        meow();
    }
};

// 派生类：Bird，只需添加自己特有的行为
class Bird : public Animal {
public:
    Bird(const std::string& name, int age) : Animal(name, age) {}

    void chirp() {
        std::cout << name_ << " says: Tweet!\n";
    }

    void makeSound() override {
        chirp();
    }
};

int main() {
    Dog dog("Buddy", 3);
    Cat cat("Whiskers", 2);
    Bird bird("Tweety", 1);

    // 继承自基类的方法可以直接使用
    dog.eat();    // 输出: Buddy is eating.
    cat.sleep();  // 输出: Whiskers is sleeping.

    // 各自特有的方法
    dog.bark();   // 输出: Buddy says: Woof!
    cat.meow();   // 输出: Whiskers says: Meow!
    bird.chirp(); // 输出: Tweety says: Tweet!

    return 0;
}
