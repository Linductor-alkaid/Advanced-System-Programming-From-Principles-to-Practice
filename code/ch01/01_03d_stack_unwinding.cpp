#include <iostream>
#include <stdexcept>
#include <string>

class Resource {
    std::string name;
public:
    Resource(const std::string& n) : name(n) {
        std::cout << "获取资源: " << name << std::endl;
    }

    ~Resource() {
        std::cout << "释放资源: " << name << std::endl;
    }
};

void dangerousFunction() {
    Resource r3("资源3");
    throw std::runtime_error("出错了!");  // 抛出异常
    // r3 的析构函数会被自动调用
}

int main() {
    std::cout << "程序开始" << std::endl;

    Resource r1("资源1");

    try {
        Resource r2("资源2");
        dangerousFunction();
        // r2 的析构函数会被调用（即使发生异常）
    }
    catch (const std::exception& e) {
        std::cout << "捕获异常: " << e.what() << std::endl;
    }

    std::cout << "程序结束" << std::endl;
    return 0;
}
