#include <iostream>

template<typename T>
class Base {
public:
    virtual void process(T value) {
        std::cout << "Base::process: " << value << "\n";
    }

    virtual ~Base() = default;
};

template<typename T>
class Derived : public Base<T> {
public:
    void process(T value) override {
        std::cout << "Derived::process: " << value << "\n";
    }
};

int main() {
    Derived<int> d;
    d.process(42);  // Derived::process: 42

    return 0;
}
