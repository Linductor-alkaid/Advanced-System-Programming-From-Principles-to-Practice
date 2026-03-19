// 04_02a_basic_thread.cpp — 线程创建的三种方式
// 编译: g++ -std=c++17 -Wall -Wextra -g -pthread -o 04_02a_basic_thread 04_02a_basic_thread.cpp

#include <iostream>
#include <thread>
#include <string>

// 方式1: 普通函数
void hello(int id) {
    std::cout << "[线程] hello from thread " << id << std::endl;
}

// 方式3: 成员函数
class Worker {
public:
    std::string name;
    explicit Worker(const std::string& n) : name(n) {}
    void run() {
        std::cout << "[线程] Worker::run, name = " << name << std::endl;
    }
};

int main() {
    std::cout << "=== 基本线程创建 ===" << std::endl;

    // 方式1: 普通函数
    std::cout << "--- 方式1: 普通函数 ---" << std::endl;
    std::thread t1(hello, 1);
    t1.join();

    // 方式2: Lambda
    std::cout << "--- 方式2: Lambda ---" << std::endl;
    int x = 42;
    std::thread t2([x]() {
        std::cout << "[线程] lambda: x = " << x << std::endl;
    });
    t2.join();

    // 方式3: 成员函数
    std::cout << "--- 方式3: 成员函数 ---" << std::endl;
    Worker w("worker1");
    std::thread t3(&Worker::run, &w);
    t3.join();

    std::cout << "=== 完成 ===" << std::endl;
    return 0;
}
