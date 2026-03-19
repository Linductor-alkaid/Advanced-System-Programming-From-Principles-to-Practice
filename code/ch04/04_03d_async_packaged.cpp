#include <iostream>
#include <thread>
#include <future>

int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

int main() {
    std::cout << "=== packaged_task 与 std::async ===" << std::endl;

    // --- packaged_task ---
    std::cout << "--- packaged_task ---" << std::endl;
    {
        std::packaged_task<int(int, int)> task(add);
        std::future<int> fut = task.get_future();

        std::thread worker(std::move(task), 3, 4);
        worker.join();

        std::cout << "[packaged_task] add(3, 4) = " << fut.get() << std::endl;
    }

    // --- std::async ---
    std::cout << "--- std::async ---" << std::endl;
    {
        std::future<int> fut = std::async(std::launch::async, multiply, 6, 7);
        std::cout << "[std::async] multiply(6, 7) = " << fut.get() << std::endl;
    }

    std::cout << "=== 完成 ===" << std::endl;
    return 0;
}
