#include <iostream>

class Animal {
public:
    int age = 0;
    void eat() {
        std::cout << "Animal eating, age: " << age << "\n";
    }
};

class Dog : public Animal {
public:
    void bark() {
        std::cout << "Woof!\n";
    }
};

class Bird : public Animal {
public:
    void fly() {
        std::cout << "Flying!\n";
    }
};

class DogBird : public Dog, public Bird {
public:
    void barkAndFly() {
        bark();
        fly();
    }
};

int main() {
    DogBird db;

    // db.age = 5;  // ❌ 编译错误：二义性
    // error: request for member 'age' is ambiguous
    // note: candidates are: int Animal::age
    // note:                 int Animal::age

    // 解决方法1：明确指定路径
    db.Dog::age = 5;
    db.Bird::age = 3;

    std::cout << "Dog::age = " << db.Dog::age << "\n";   // 5
    std::cout << "Bird::age = " << db.Bird::age << "\n"; // 3

    // 问题：Dog中的Animal和Bird中的Animal是两个不同的对象！

    return 0;
}
