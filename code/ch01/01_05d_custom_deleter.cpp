#include <iostream>
#include <memory>
#include <fstream>
#include <cstdio>

// 示例1：管理 FILE* 的删除器
struct FileDeleter {
    void operator()(FILE* f) const {
        if (f) {
            std::fclose(f);
            std::cout << "文件已关闭 (FILE*)\n";
        }
    }
};

using UniqueFile = std::unique_ptr<FILE, FileDeleter>;

// 示例2：管理数组
struct ArrayDeleter {
    void operator()(int* p) const {
        delete[] p;
        std::cout << "数组已删除\n";
    }
};

using UniqueIntArray = std::unique_ptr<int, ArrayDeleter>;

// 示例3：带日志的删除器
template<typename T>
struct LoggedDeleter {
    void operator()(T* p) const {
        std::cout << "即将删除对象\n";
        delete p;
        std::cout << "对象已删除\n";
    }
};

void custom_deleter_demo() {
    std::cout << "=== FILE* 删除器 ===\n";
    {
        UniqueFile file(std::fopen("test.txt", "w"));
        if (file) {
            std::fprintf(file.get(), "Hello, World!\n");
            std::cout << "文件已写入\n";
        }
    }
    // file 离开作用域，自动调用 fclose

    std::cout << "\n=== 数组删除器 ===\n";
    {
        UniqueIntArray arr(new int[5]);
        arr.get()[0] = 42;
        std::cout << "arr[0] = " << arr.get()[0] << "\n";
    }
    // arr 离开作用域，自动调用 delete[]

    std::cout << "\n=== 带日志的删除器 ===\n";
    {
        std::unique_ptr<int, LoggedDeleter<int>> p(new int(100));
        std::cout << "*p = " << *p << "\n";
    }
}

// 示例4：使用 lambda 作为删除器
void lambda_deleter_demo() {
    std::cout << "\n=== Lambda 删除器 ===\n";

    auto deleter = [](void* p) {
        std::cout << "Lambda 删除器被调用\n";
        // 假设这是某种特殊的释放操作
        ::operator delete(p);
    };

    std::unique_ptr<void, decltype(deleter)> p(
        ::operator new(1024), deleter
    );

    std::cout << "分配了 1024 字节内存\n";
}
// p 离开作用域，lambda 删除器被调用

int main() {
    custom_deleter_demo();
    lambda_deleter_demo();
    return 0;
}
