#include <iostream>
#include <algorithm>
#include <stdexcept>

class DynamicArray {
    int* data = nullptr;
    size_t size = 0;

public:
    // 构造函数：分配内存
    explicit DynamicArray(size_t n) : size(n) {
        data = new int[n];
        std::cout << "已分配 " << n << " 个 int" << std::endl;
    }

    // 析构函数：释放内存
    ~DynamicArray() {
        delete[] data;
        std::cout << "已释放内存" << std::endl;
    }

    // 禁止拷贝
    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;

    // 允许移动
    DynamicArray(DynamicArray&& other) noexcept
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    // 访问元素
    int& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("索引越界");
        return data[index];
    }

    const int& operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("索引越界");
        return data[index];
    }

    size_t get_size() const { return size; }
};

// 使用示例
void process_array() {
    DynamicArray arr(5);

    for (size_t i = 0; i < arr.get_size(); ++i) {
        arr[i] = static_cast<int>(i * 10);
    }

    // 发生异常？内存会自动释放！
    if (arr[0] == 0) {
        throw std::runtime_error("模拟异常");
    }
}

int main() {
    try {
        process_array();
    } catch (const std::exception& e) {
        std::cout << "捕获异常: " << e.what() << std::endl;
    }
    return 0;
}
