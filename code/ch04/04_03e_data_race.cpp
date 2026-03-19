// ⚠️ 数据竞争（Data Race）演示
// 期望值: 100000，实际值可能小于该值
// 这是未定义行为（UB），但在 x86-64 上通常不会崩溃
// 可用 g++ -fsanitize=thread 编译来检测数据竞争
// 解决方案：见 4.4 节（原子操作）或第5章（互斥锁）

#include <iostream>
#include <thread>
#include <vector>

int counter = 0;

int main() {
    std::cout << "=== 数据竞争演示 ===" << std::endl;

    const int num_threads = 10;
    const int increments_per_thread = 10000;

    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([]{
            for (int j = 0; j < increments_per_thread; ++j) {
                counter++;  // 数据竞争！
            }
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "期望值: " << num_threads * increments_per_thread << std::endl;
    std::cout << "实际值: " << counter << std::endl;

    if (counter != num_threads * increments_per_thread) {
        std::cout << "发生了数据竞争，结果不正确！" << std::endl;
    } else {
        std::cout << "本次运行未观察到数据竞争（但问题仍然存在）" << std::endl;
    }

    std::cout << "=== 完成 ===" << std::endl;
    return 0;
}
