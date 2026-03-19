#include <iostream>
#include <memory>

class Base {
public:
    virtual Base* clone() {
        std::cout << "Base::clone\n";
        return new Base(*this);
    }

    virtual ~Base() = default;
};

class Derived : public Base {
public:
    // 协变返回类型：允许返回 Derived* 覆盖 Base*
    Derived* clone() override {
        std::cout << "Derived::clone\n";
        return new Derived(*this);
    }
};

// 更实用的例子
class Animal {
public:
    virtual Animal* create() {
        std::cout << "Creating generic animal\n";
        return new Animal();
    }

    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    // 协变返回：返回更具体的类型
    Dog* create() override {
        std::cout << "Creating dog\n";
        return new Dog();
    }

    void bark() {
        std::cout << "Woof!\n";
    }
};

int main() {
    Dog d;
    Animal* a = &d;

    Animal* clonedAnimal = a->create();  // 返回 Animal*
    Dog* specificDog = dynamic_cast<Dog*>(clonedAnimal);
    if (specificDog) {
        specificDog->bark();
    }

    // 使用 Dog 指针时，可以直接得到 Dog*
    Dog dog;
    Dog* clonedDog = dog.create();  // 返回 Dog*，不需要转换
    clonedDog->bark();

    delete clonedAnimal;
    delete clonedDog;
    return 0;
}
