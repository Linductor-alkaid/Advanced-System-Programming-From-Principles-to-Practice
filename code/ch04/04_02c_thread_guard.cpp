// 04_02c_thread_guard.cpp — RAII 线程守护类
// 编译: g++ -std=c++17 -Wall -Wextra -g -pthread -o 04_02c_thread_guard 04_02c_thread_guard.cpp

#include <iostream>
#include <thread>
#include <stdexcept>

class ThreadGuard {
    std::thread& t_;
public:
    explicit ThreadGuard(std::thread& t) : t_(t) {}

    ~ThreadGuard() {
        if (t_.joinable()) {
            std::cout << "[ThreadGuard] 析构函数中自动 join 线程" << std::endl;
            t_.join();
        }
    }

    // 禁止拷贝
    ThreadGuard(const ThreadGuard&) = delete;
    ThreadGuard& operator=(const ThreadGuard&) = delete;
};

void demo_normal_path() {
    std::cout << "--- 场景1: 正常路径 ---" << std::endl;

    std::thread t([]() {
        std::cout << "[线程] 正常路径中的工作线程" << std::endl;
    });

    ThreadGuard guard(t);
    std::cout << "[主线程] 函数即将返回，ThreadGuard 将自动 join" << std::endl;
    // guard 析构时自动 join
}

void demo_exception_path() {
    std::cout << "--- 场景2: 异常路径 ---" << std::endl;

    std::thread t([]() {
        std::cout << "[线程] 异常路径中的工作线程" << std::endl;
    });

    ThreadGuard guard(t);

    try {
        std::cout << "[主线程] 模拟抛出异常..." << std::endl;
        throw std::runtime_error("模拟异常");
    } catch (const std::exception& e) {
        std::cout << "[主线程] 捕获异常: " << e.what() << std::endl;
    }
    // guard 析构时自动 join，即使发生了异常
}

int main() {
    std::cout << "=== ThreadGuard RAII 示例 ===" << std::endl;

    demo_normal_path();
    std::cout << std::endl;
    demo_exception_path();

    std::cout << "=== 完成 ===" << std::endl;
    return 0;
}
