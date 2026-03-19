// 04_01c_overhead_compare.cpp — 进程 vs 线程创建开销对比
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    const int COUNT = 1000;

    std::cout << "=== 进程 vs 线程 创建开销对比 ===" << std::endl;
    std::cout << "创建数量: " << COUNT << std::endl;

    // 线程基准测试
    {
        auto start = std::chrono::high_resolution_clock::now();

        std::vector<std::thread> threads;
        threads.reserve(COUNT);
        for (int i = 0; i < COUNT; ++i) {
            threads.emplace_back([]() {});
        }
        for (auto& t : threads) {
            t.join();
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "线程创建+回收: " << ms << " ms" << std::endl;
    }

    // 进程基准测试
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < COUNT; ++i) {
            pid_t pid = fork();
            if (pid < 0) {
                std::cerr << "fork() 失败" << std::endl;
                return 1;
            }
            if (pid == 0) {
                _exit(0);
            }
            waitpid(pid, nullptr, 0);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "进程创建+回收: " << ms << " ms" << std::endl;
    }

    return 0;
}
