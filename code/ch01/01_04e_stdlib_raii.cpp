#include <iostream>
#include <memory>      // std::unique_ptr, std::shared_ptr
#include <mutex>       // std::lock_guard
#include <fstream>     // std::fstream
#include <vector>

// 标准库已经提供了许多 RAII 类！

void standard_raii_demo() {
    // 1. std::unique_ptr：独占所有权智能指针
    std::cout << "=== std::unique_ptr ===" << std::endl;
    {
        std::unique_ptr<int> ptr(new int(42));
        std::cout << "值: " << *ptr << std::endl;
        // 离开作用域，自动 delete
    }
    std::cout << "unique_ptr 已释放" << std::endl;

    // 2. std::shared_ptr：共享所有权智能指针
    std::cout << "\n=== std::shared_ptr ===" << std::endl;
    {
        auto shared = std::make_shared<int>(100);
        std::cout << "引用计数: " << shared.use_count() << std::endl;

        {
            auto shared2 = shared;  // 引用计数 +1
            std::cout << "引用计数: " << shared.use_count() << std::endl;
        }
        // shared2 离开作用域，引用计数 -1

        std::cout << "引用计数: " << shared.use_count() << std::endl;
    }
    // shared 离开作用域，内存被释放

    // 3. std::lock_guard：自动管理互斥锁
    std::cout << "\n=== std::lock_guard ===" << std::endl;
    {
        std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);  // 自动加锁
        // 临界区代码
        std::cout << "锁已持有" << std::endl;
    }
    std::cout << "锁已释放" << std::endl;

    // 4. std::fstream：自动管理文件句柄
    std::cout << "\n=== std::fstream ===" << std::endl;
    {
        std::ofstream file("example.txt");
        file << "Hello, RAII!" << std::endl;
        // 离开作用域，文件自动关闭
    }
    std::cout << "文件已关闭" << std::endl;

    // 5. std::vector：自动管理动态数组
    std::cout << "\n=== std::vector ===" << std::endl;
    {
        std::vector<int> vec = {1, 2, 3, 4, 5};
        std::cout << "大小: " << vec.size() << std::endl;
    }
    std::cout << "vector 内存已释放" << std::endl;
}

int main() {
    standard_raii_demo();
    return 0;
}
