#include <iostream>
#include <thread>

thread_local int counter = 0;

int main() {
    std::cout << "=== thread_local 变量演示 ===" << std::endl;

    for (int i = 0; i < 3; ++i) {
        std::thread t([i]{
            int times = i + 1;
            for (int j = 0; j < times; ++j) {
                ++counter;
            }
            std::cout << "[线程" << i << "] counter 递增 " << times
                      << " 次, 最终值: " << counter << std::endl;
        });
        t.join();
    }

    std::cout << "[主线程] 各线程的 counter 独立，互不影响" << std::endl;
    std::cout << "[主线程] 主线程的 counter: " << counter
              << " (未被任何工作线程修改)" << std::endl;

    std::cout << "=== 完成 ===" << std::endl;
    return 0;
}
