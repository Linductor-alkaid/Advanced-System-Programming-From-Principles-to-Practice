# 附录A：开发环境搭建

> [返回目录](../README.md)

## A.1 Linux环境安装

### A.1.1 虚拟机安装
推荐使用Oracle VirtualBox或VMware Workstation安装Ubuntu 20.04/22.04。

### A.1.2 WSL2（Windows用户）
Windows 10/11用户可以使用WSL2安装Ubuntu。

## A.2 开发工具安装

```bash
# 更新软件源
sudo apt update

# 安装基础开发工具
sudo apt install build-essential cmake gdb

# 安装常用库
sudo apt install libboost-all-dev

# 安装性能分析工具
sudo apt install valgrind perf

# 内核开发工具
sudo apt install linux-headers-$(uname -r)
```

## A.3 编译器版本

```bash
# 检查GCC版本
gcc --version  # 推荐9.0+

# 检查C++标准支持
gcc -std=c++17 ...
```

---

*编写中...*
