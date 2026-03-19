// 04_01a_fork_demo.cpp — fork() 创建子进程，演示 Copy-on-Write 地址空间隔离
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int globalVar = 100;

int main() {
    int localVar = 200;

    std::cout << "=== 进程创建与资源隔离 ===" << std::endl;
    std::cout << "父进程 PID: " << getpid() << std::endl;
    std::cout << std::endl;

    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "fork() 失败" << std::endl;
        return 1;
    }

    if (pid == 0) {
        // 子进程
        globalVar = 999;
        localVar = 888;
        std::cout << "[子进程] PID: " << getpid()
                  << ", 父进程PID: " << getppid() << std::endl;
        std::cout << "[子进程] globalVar = " << globalVar
                  << " (地址: 0x" << std::hex
                  << reinterpret_cast<uintptr_t>(&globalVar) << ")" << std::endl;
        std::cout << "[子进程] localVar = " << std::dec << localVar
                  << " (地址: 0x" << std::hex
                  << reinterpret_cast<uintptr_t>(&localVar) << ")" << std::endl;
        _exit(0);
    }

    // 父进程
    int status;
    waitpid(pid, &status, 0);

    std::cout << std::endl;
    std::cout << "[父进程] 子进程退出后：" << std::endl;
    std::cout << "[父进程] globalVar = " << globalVar
              << " (地址: 0x" << std::hex
              << reinterpret_cast<uintptr_t>(&globalVar) << ")" << std::endl;
    std::cout << "[父进程] localVar = " << std::dec << localVar
              << " (地址: 0x" << std::hex
              << reinterpret_cast<uintptr_t>(&localVar) << ")" << std::endl;
    std::cout << "[父进程] 变量未被子进程修改 ── 地址空间隔离！" << std::endl;

    return 0;
}
