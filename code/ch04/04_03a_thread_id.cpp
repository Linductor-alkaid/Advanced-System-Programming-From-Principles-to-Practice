#include <iostream>
#include <thread>
#include <chrono>

int main() {
    std::cout << "=== 线程标识与工具函数 ===" << std::endl;

    auto main_id = std::this_thread::get_id();
    std::cout << "[主线程] ID: " << main_id << std::endl;

    std::thread worker([]{
        std::cout << "[工作线程] ID: " << std::this_thread::get_id() << std::endl;
        std::cout << "[工作线程] 休眠 100ms..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "[工作线程] yield 让出 CPU" << std::endl;
        std::this_thread::yield();
        std::cout << "[工作线程] 完成" << std::endl;
    });

    worker.join();

    std::thread::id default_id{};
    std::cout << "[主线程] 默认 thread::id 表示无线程: " << default_id << std::endl;
    std::cout << "[主线程] 主线程ID != 默认ID: "
              << (main_id != default_id ? "true" : "false") << std::endl;

    std::cout << "=== 完成 ===" << std::endl;
    return 0;
}
