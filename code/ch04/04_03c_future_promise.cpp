#include <iostream>
#include <thread>
#include <future>
#include <stdexcept>
#include <chrono>
#include <atomic>

int main() {
    std::cout << "=== future/promise 异步通信 ===" << std::endl;

    // --- 基本用法 ---
    std::cout << "--- 基本用法 ---" << std::endl;
    {
        std::promise<int> prom;
        std::future<int> fut = prom.get_future();
        std::atomic<bool> main_printed{false};

        std::thread worker([&prom, &main_printed]{
            // 等待主线程先打印"等待结果"
            while (!main_printed.load()) {
                std::this_thread::yield();
            }
            int result = 42;
            std::cout << "[工作线程] 计算完成，设置结果" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            prom.set_value(result);
        });

        std::cout << "[主线程] 等待结果..." << std::endl;
        main_printed.store(true);
        int value = fut.get();
        std::cout << "[主线程] 收到结果: " << value << std::endl;

        worker.join();
    }

    // --- 异常传播 ---
    std::cout << "--- 异常传播 ---" << std::endl;
    {
        std::promise<int> prom;
        std::future<int> fut = prom.get_future();

        std::thread worker([&prom]{
            prom.set_exception(
                std::make_exception_ptr(
                    std::runtime_error("计算过程中发生错误")));
        });

        worker.join();

        try {
            fut.get();
        } catch (const std::exception& e) {
            std::cout << "[主线程] 捕获异常: " << e.what() << std::endl;
        }
    }

    std::cout << "=== 完成 ===" << std::endl;
    return 0;
}
