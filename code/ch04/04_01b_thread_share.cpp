// 04_01b_thread_share.cpp — std::thread 共享全局变量演示
#include <iostream>
#include <thread>

int sharedVar = 100;

void threadFunc(int id) {
    std::cout << "[线程 " << id << "] sharedVar 地址: 0x"
              << std::hex << reinterpret_cast<uintptr_t>(&sharedVar)
              << std::dec << std::endl;
    sharedVar += id * 10;
    std::cout << "[线程 " << id << "] sharedVar += " << id * 10
              << " → " << sharedVar << std::endl;
}

int main() {
    std::cout << "=== 线程共享地址空间 ===" << std::endl;
    std::cout << "主线程 sharedVar = " << sharedVar << std::endl;

    std::thread t1(threadFunc, 1);
    std::thread t2(threadFunc, 2);

    t1.join();
    t2.join();

    std::cout << "主线程 sharedVar = " << sharedVar << std::endl;

    return 0;
}
// 注意：本示例存在数据竞争（data race）。两个线程同时读写 sharedVar
// 而没有任何同步机制（如 mutex 或 atomic），在实际生产代码中这是未定义行为。
