#include <iostream>
#include <string>

class Tracer {
    std::string name;
public:
    Tracer(const std::string& n) : name(n) {
        std::cout << "构造: " << name << std::endl;
    }

    ~Tracer() {
        std::cout << "析构: " << name << std::endl;
    }
};

void functionB() {
    std::cout << "进入 functionB" << std::endl;
    Tracer t4("functionB::t4");
    std::cout << "离开 functionB" << std::endl;
}

void functionA() {
    std::cout << "进入 functionA" << std::endl;
    Tracer t2("functionA::t2");
    Tracer t3("functionA::t3");
    functionB();
    std::cout << "离开 functionA" << std::endl;
}

int main() {
    std::cout << "===== main 开始 =====" << std::endl;
    Tracer t1("main::t1");
    functionA();
    std::cout << "===== main 结束 =====" << std::endl;
    return 0;
}
