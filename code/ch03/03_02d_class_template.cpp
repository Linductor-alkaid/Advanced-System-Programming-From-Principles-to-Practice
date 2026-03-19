#include <iostream>
#include <vector>
#include <cassert>
#include <string>

// 类模板：通用容器
template<typename T>
class Stack {
private:
    std::vector<T> data_;

public:
    void push(const T& value) {
        data_.push_back(value);
    }

    T pop() {
        assert(!data_.empty());
        T value = data_.back();
        data_.pop_back();
        return value;
    }

    const T& top() const {
        assert(!data_.empty());
        return data_.back();
    }

    bool empty() const {
        return data_.empty();
    }

    size_t size() const {
        return data_.size();
    }
};

// 策略模式的静态多态实现
template<typename Strategy>
class Context {
private:
    Strategy strategy_;

public:
    void execute() {
        strategy_.execute();
    }
};

class ConcreteStrategyA {
public:
    void execute() {
        std::cout << "Executing Strategy A\n";
    }
};

class ConcreteStrategyB {
public:
    void execute() {
        std::cout << "Executing Strategy B\n";
    }
};

int main() {
    // 类模板实例化
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    std::cout << "Top: " << intStack.top() << "\n";
    intStack.pop();
    std::cout << "Size: " << intStack.size() << "\n";

    Stack<std::string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");

    // 静态多态的策略模式
    Context<ConcreteStrategyA> contextA;
    contextA.execute();  // 输出: Executing Strategy A

    Context<ConcreteStrategyB> contextB;
    contextB.execute();  // 输出: Executing Strategy B

    return 0;
}
