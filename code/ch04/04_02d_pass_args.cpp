// 04_02d_pass_args.cpp — 线程参数传递的三种方式
// 编译: g++ -std=c++17 -Wall -Wextra -g -pthread -o 04_02d_pass_args 04_02d_pass_args.cpp

#include <iostream>
#include <thread>
#include <memory>
#include <string>
#include <functional>

int main() {
    std::cout << "=== 线程参数传递 ===" << std::endl;

    // --- 值传递 ---
    std::cout << "--- 值传递 ---" << std::endl;
    {
        int val = 42;
        std::thread t([](int v) {
            v = 100;
            std::cout << "[线程] 收到值: 42, 修改为: " << v << std::endl;
        }, val);
        t.join();
        std::cout << "[主线程] 原始值未变: " << val << std::endl;
    }

    // --- 引用传递 ---
    std::cout << "--- 引用传递 ---" << std::endl;
    {
        int val = 42;
        std::thread t([](int& v) {
            v = 100;
            std::cout << "[线程] 收到引用, 修改为: " << v << std::endl;
        }, std::ref(val));
        t.join();
        std::cout << "[主线程] 值已被修改: " << val << std::endl;
    }

    // --- 移动语义 ---
    std::cout << "--- 移动语义 ---" << std::endl;
    {
        auto ptr = std::make_unique<std::string>("hello");
        std::thread t([](std::unique_ptr<std::string> p) {
            std::cout << "[线程] 收到 unique_ptr, 值: " << *p << std::endl;
        }, std::move(ptr));
        t.join();
        std::cout << "[主线程] unique_ptr 已转移 (nullptr)" << std::endl;
    }

    std::cout << "=== 完成 ===" << std::endl;
    return 0;
}
