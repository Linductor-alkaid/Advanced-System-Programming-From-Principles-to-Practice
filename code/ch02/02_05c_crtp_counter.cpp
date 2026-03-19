#include <iostream>
#include <string>

// CRTP 对象计数基类
template <typename Derived>
class ObjectCounter {
protected:
    ObjectCounter() {
        ++count_;
    }

    ObjectCounter(const ObjectCounter&) {
        ++count_;
    }

    ObjectCounter(ObjectCounter&&) {
        ++count_;
    }

    ~ObjectCounter() {
        --count_;
    }

public:
    static size_t getCount() {
        return count_;
    }

private:
    inline static size_t count_ = 0;
};

// 使用对象计数
class User : public ObjectCounter<User> {
    std::string name_;
public:
    User(const std::string& name) : name_(name) {
        std::cout << "User " << name_ << " created\n";
    }
};

class Product : public ObjectCounter<Product> {
    std::string name_;
public:
    Product(const std::string& name) : name_(name) {
        std::cout << "Product " << name_ << " created\n";
    }
};

int main() {
    std::cout << "Initial User count: " << User::getCount() << "\n";  // 0
    std::cout << "Initial Product count: " << Product::getCount() << "\n";  // 0

    {
        User u1("Alice");
        User u2("Bob");
        std::cout << "User count: " << User::getCount() << "\n";  // 2

        Product p1("Laptop");
        std::cout << "Product count: " << Product::getCount() << "\n";  // 1
        std::cout << "User count: " << User::getCount() << "\n";  // 2 (独立计数)
    }

    std::cout << "After scope, User count: " << User::getCount() << "\n";  // 0
    std::cout << "After scope, Product count: " << Product::getCount() << "\n";  // 0

    return 0;
}
