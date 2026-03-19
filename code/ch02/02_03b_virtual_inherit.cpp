#include <iostream>

class Animal {
public:
    int age = 0;
    void eat() {
        std::cout << "Animal eating, age: " << age << "\n";
    }
};

// 使用 virtual 继承，表示 Animal 是虚基类
class Dog : virtual public Animal {
public:
    void bark() {
        std::cout << "Woof!\n";
    }
};

class Bird : virtual public Animal {
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

    // ✅ 不再有二义性：只有一个 Animal 子对象
    db.age = 5;
    std::cout << "db.age = " << db.age << "\n";  // 5

    db.eat();  // 输出: Animal eating, age: 5

    // 通过任何路径访问的都是同一个 Animal 对象
    db.Dog::age = 10;
    std::cout << "db.Bird::age = " << db.Bird::age << "\n";  // 10（同一个对象）

    return 0;
}
