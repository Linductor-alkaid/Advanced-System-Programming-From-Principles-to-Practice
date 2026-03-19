// 04_02b_detach_risk.cpp — detach 导致的未定义行为示例
// 编译: g++ -std=c++17 -Wall -Wextra -g -pthread -o 04_02b_detach_risk 04_02b_detach_risk.cpp
// ⚠️ 仅编译，不要运行！

// ⚠️ WARNING: 这段代码包含未定义行为（UB）！
// 仅作为教学示例，不要在实际项目中这样写。
// 可用 g++ -fsanitize=address 编译来观察实际错误。
// 正确做法：使用 shared_ptr 或确保线程在数据销毁前完成。

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <numeric>

void dangerousDetach() {
    std::vector<int> data = {1, 2, 3, 4, 5};

    std::thread t([&data]() {
        // 线程休眠 100ms，此时 dangerousDetach() 可能已经返回
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // ⚠️ UB: data 已被销毁，访问悬空引用！
        int sum = std::accumulate(data.begin(), data.end(), 0);
        std::cout << "[线程] sum = " << sum << std::endl;
    });

    // detach 后函数返回，data 被销毁
    t.detach();
    std::cout << "[主线程] dangerousDetach 返回，data 即将销毁" << std::endl;
}

int main() {
    std::cout << "=== detach 风险示例 ===" << std::endl;

    dangerousDetach();

    // 等待足够长时间让分离的线程尝试访问已销毁的数据
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    std::cout << "=== 完成 ===" << std::endl;
    return 0;
}
