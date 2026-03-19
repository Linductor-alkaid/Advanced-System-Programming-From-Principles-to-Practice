#include <iostream>

// CRTP 基类
template <typename Derived>
class Animal {
public:
    // 基类定义接口，调用派生类实现
    void speak() {
        static_cast<Derived*>(this)->speakImpl();
    }

    void move() {
        static_cast<Derived*>(this)->moveImpl();
    }

    // 默认实现（可选）
    void sleep() {
        std::cout << "Sleeping...\n";
    }
};

// 派生类：Dog
class Dog : public Animal<Dog> {
public:
    void speakImpl() {
        std::cout << "Woof!\n";
    }

    void moveImpl() {
        std::cout << "Running on four legs\n";
    }
};

// 派生类：Cat
class Cat : public Animal<Cat> {
public:
    void speakImpl() {
        std::cout << "Meow!\n";
    }

    void moveImpl() {
        std::cout << "Prowling silently\n";
    }
};

// 派生类：Bird（可选覆盖 sleep）
class Bird : public Animal<Bird> {
public:
    void speakImpl() {
        std::cout << "Tweet!\n";
    }

    void moveImpl() {
        std::cout << "Flying\n";
    }
};

int main() {
    Dog dog;
    Cat cat;
    Bird bird;

    dog.speak();   // 输出: Woof!
    dog.move();    // 输出: Running on four legs
    dog.sleep();   // 输出: Sleeping...

    cat.speak();   // 输出: Meow!
    cat.move();    // 输出: Prowling silently

    bird.speak();  // 输出: Tweet!
    bird.move();   // 输出: Flying

    // 编译期确定调用，无虚函数开销
    return 0;
}
