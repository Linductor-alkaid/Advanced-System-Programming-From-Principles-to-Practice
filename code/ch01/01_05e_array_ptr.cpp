#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>

void unique_ptr_array_demo() {
    std::cout << "=== unique_ptr 管理数组 ===\n";

    // 方式1：使用 unique_ptr<T[]>（推荐）
    {
        std::unique_ptr<int[]> arr(new int[5]);
        for (int i = 0; i < 5; ++i) {
            arr[i] = i * 10;  // 使用 operator[] 访问
        }

        std::cout << "数组内容: ";
        for (int i = 0; i < 5; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";
    }
    // 自动调用 delete[]

    // 方式2：使用 unique_ptr<vector>（更灵活）
    {
        auto vec = std::make_unique<std::vector<int>>(std::initializer_list<int>{1, 2, 3, 4, 5});
        std::cout << "Vector 大小: " << vec->size() << "\n";

        for (int v : *vec) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }

    // 方式3：使用 std::make_unique for arrays (C++20)
    #if __cplusplus >= 202002L
    {
        auto arr = std::make_unique<int[]>(5);
        arr[0] = 100;
        std::cout << "C++20 make_unique array: " << arr[0] << "\n";
    }
    #endif

    std::cout << "\n=== 离开作用域 ===\n";
}

int main() {
    unique_ptr_array_demo();
    return 0;
}
