#include <iostream>
#include <cstdio>
#include <stdexcept>

class File {
    std::FILE* handle = nullptr;

public:
    // 构造函数：打开文件
    explicit File(const char* filename, const char* mode = "r") {
        handle = std::fopen(filename, mode);
        if (!handle) {
            throw std::runtime_error("无法打开文件");
        }
        std::cout << "文件已打开: " << filename << std::endl;
    }

    // 析构函数：关闭文件
    ~File() {
        if (handle) {
            std::fclose(handle);
            std::cout << "文件已关闭" << std::endl;
        }
    }

    // 禁止拷贝
    File(const File&) = delete;
    File& operator=(const File&) = delete;

    // 允许移动
    File(File&& other) noexcept : handle(other.handle) {
        other.handle = nullptr;
    }

    File& operator=(File&& other) noexcept {
        if (this != &other) {
            if (handle) std::fclose(handle);
            handle = other.handle;
            other.handle = nullptr;
        }
        return *this;
    }

    // 访问底层句柄
    std::FILE* get() const { return handle; }

    // 写入数据
    void write(const char* data) {
        if (handle) {
            std::fputs(data, handle);
        }
    }
};

// 使用示例
void process_data() {
    File file("test.txt", "w");

    file.write("Hello, RAII!\n");

    // 无论这里发生什么，file 都会被正确关闭
    if (true) {
        return;  // 提前返回，文件自动关闭
    }
}

int main() {
    process_data();
    return 0;
}
