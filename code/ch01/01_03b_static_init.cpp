#include <iostream>
#include <string>

class Tracer {
    std::string name;
    int id;
    static int count;
public:
    Tracer(const std::string& n) : name(n), id(++count) {
        std::cout << "[" << id << "] 构造: " << name << std::endl;
    }

    ~Tracer() {
        std::cout << "[" << id << "] 析构: " << name << std::endl;
    }
};

int Tracer::count = 0;

// 全局对象：在 main() 之前构造
Tracer global1("全局对象1");
Tracer global2("全局对象2");

Tracer& getStaticRef() {
    static Tracer localStatic("函数内静态对象");  // 第一次调用时构造
    return localStatic;
}

int main() {
    std::cout << "===== main 开始 =====" << std::endl;

    // 局部静态对象：第一次经过时构造
    getStaticRef();
    getStaticRef();  // 不会再次构造

    std::cout << "===== main 结束 =====" << std::endl;
    return 0;
}
