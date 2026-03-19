#include <iostream>
#include <mutex>
#include <thread>

class ScopedLock {
    std::mutex& mtx;
    bool locked = true;

public:
    explicit ScopedLock(std::mutex& m) : mtx(m) {
        mtx.lock();
        std::cout << "锁已获取" << std::endl;
    }

    ~ScopedLock() {
        if (locked) {
            mtx.unlock();
            std::cout << "锁已释放" << std::endl;
        }
    }

    // 禁止拷贝和移动
    ScopedLock(const ScopedLock&) = delete;
    ScopedLock& operator=(const ScopedLock&) = delete;
    ScopedLock(ScopedLock&&) = delete;
    ScopedLock& operator=(ScopedLock&&) = delete;

    // 手动解锁（可选）
    void unlock() {
        if (locked) {
            mtx.unlock();
            locked = false;
        }
    }
};

// 共享资源
int shared_counter = 0;
std::mutex counter_mutex;

void safe_increment() {
    ScopedLock lock(counter_mutex);  // 构造时加锁

    // 临界区：安全地访问共享资源
    ++shared_counter;
    std::cout << "计数器值: " << shared_counter << std::endl;

    // 离开作用域，自动解锁
}

int main() {
    std::thread t1(safe_increment);
    std::thread t2(safe_increment);

    t1.join();
    t2.join();

    return 0;
}
