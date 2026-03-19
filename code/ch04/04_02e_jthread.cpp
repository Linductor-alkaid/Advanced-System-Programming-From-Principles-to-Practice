// 04_02e_jthread.cpp — C++20 std::jthread 与 stop_token
// 编译 C++20: g++ -std=c++20 -Wall -Wextra -g -pthread -o 04_02e_jthread 04_02e_jthread.cpp
// 编译 C++17: g++ -std=c++17 -Wall -Wextra -g -pthread -o 04_02e_jthread 04_02e_jthread.cpp

#include <iostream>
#include <thread>
#include <chrono>

#if __cplusplus >= 202002L && __has_include(<stop_token>)
#include <stop_token>

void worker(std::stop_token stoken) {
    int count = 0;
    while (!stoken.stop_requested()) {
        std::cout << "[jthread] 工作中... count = " << ++count << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::cout << "[jthread] 收到停止请求，退出" << std::endl;
}

int main() {
    std::cout << "=== std::jthread 示例 (C++20) ===" << std::endl;

    {
        std::jthread jt(worker);
        std::this_thread::sleep_for(std::chrono::milliseconds(180));
        std::cout << "[主线程] 请求停止..." << std::endl;
        jt.request_stop();
        // jthread 析构时自动 join
    }

    std::cout << "=== 完成 ===" << std::endl;
    return 0;
}

#else

int main() {
    std::cout << "std::jthread 需要 C++20 支持，当前编译器不支持" << std::endl;
    return 0;
}

#endif
