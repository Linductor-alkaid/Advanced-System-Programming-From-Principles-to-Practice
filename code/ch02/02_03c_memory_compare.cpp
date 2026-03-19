#include <iostream>

// 非虚继承版本
class Animal {
public:
    int age = 0;
};

class Dog : public Animal {
public:
    int dogData = 1;
};

class Bird : public Animal {
public:
    int birdData = 2;
};

class DogBird : public Dog, public Bird {
public:
    int dogBirdData = 3;
};

// 虚继承版本
class VAnimal {
public:
    int age = 0;
};

class VDog : virtual public VAnimal {
public:
    int dogData = 1;
};

class VBird : virtual public VAnimal {
public:
    int birdData = 2;
};

class VDogBird : public VDog, public VBird {
public:
    int dogBirdData = 3;
};

int main() {
    std::cout << "=== 内存大小对比 ===\n\n";

    std::cout << "非虚继承:\n";
    std::cout << "  sizeof(Dog)    = " << sizeof(Dog) << "\n";
    std::cout << "  sizeof(Bird)   = " << sizeof(Bird) << "\n";
    std::cout << "  sizeof(DogBird)= " << sizeof(DogBird) << "\n";

    std::cout << "\n虚继承:\n";
    std::cout << "  sizeof(VDog)    = " << sizeof(VDog) << "\n";
    std::cout << "  sizeof(VBird)   = " << sizeof(VBird) << "\n";
    std::cout << "  sizeof(VDogBird)= " << sizeof(VDogBird) << "\n";

    std::cout << "\n=== 分析 ===\n";
    std::cout << "非虚继承 DogBird 包含两份 Animal，sizeof = 2 * sizeof(Animal) + 成员\n";
    std::cout << "虚继承 VDogBird 只有一份 Animal，但需要额外的指针开销\n";

    return 0;
}
