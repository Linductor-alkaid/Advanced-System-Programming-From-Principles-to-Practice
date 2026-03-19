#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <memory>
#include <thread>
#include <vector>
#include <chrono>

// RAII：管理文件句柄
class LogFile {
    std::ofstream file;
    std::mutex mtx;  // 每个日志文件有自己的互斥锁

public:
    explicit LogFile(const std::string& filename) {
        file.open(filename, std::ios::app);
        if (!file.is_open()) {
            throw std::runtime_error("无法打开日志文件");
        }
    }

    ~LogFile() {
        if (file.is_open()) {
            file.close();
        }
    }

    // 禁止拷贝
    LogFile(const LogFile&) = delete;
    LogFile& operator=(const LogFile&) = delete;

    // 线程安全的写入
    void write(const std::string& message) {
        std::lock_guard<std::mutex> lock(mtx);
        file << message << std::endl;
        file.flush();  // 确保立即写入
    }
};

// RAII：自动添加时间戳的日志记录器
class ScopedTimer {
    std::string name;
    std::shared_ptr<LogFile> logger;
    std::chrono::steady_clock::time_point start;

public:
    ScopedTimer(const std::string& n, std::shared_ptr<LogFile> log)
        : name(n), logger(log), start(std::chrono::steady_clock::now()) {}

    ~ScopedTimer() {
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        logger->write("[" + name + "] 耗时: " + std::to_string(duration.count()) + "ms");
    }
};

// 使用示例
void worker_thread(int id, std::shared_ptr<LogFile> logger) {
    {
        ScopedTimer timer("线程" + std::to_string(id), logger);
        // 模拟工作
        std::this_thread::sleep_for(std::chrono::milliseconds(100 + id * 50));
    }
    // timer 析构，自动记录耗时
}

int main() {
    auto logger = std::make_shared<LogFile>("app.log");

    logger->write("=== 程序启动 ===");

    {
        std::vector<std::thread> threads;

        for (int i = 0; i < 3; ++i) {
            threads.emplace_back(worker_thread, i, logger);
        }

        for (auto& t : threads) {
            t.join();
        }
    }

    logger->write("=== 程序结束 ===");

    // 读取并打印日志文件内容
    std::cout << "日志文件内容:" << std::endl;
    std::ifstream logRead("app.log");
    std::string line;
    while (std::getline(logRead, line)) {
        std::cout << line << std::endl;
    }

    return 0;
}
